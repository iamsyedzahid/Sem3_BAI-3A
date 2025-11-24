;============================================================================
;
; IMAGE-AWARE HYBRID RLE ENCODER/DECODER
; COMPLETE VERSION WITH GRAYSCALE SUPPORT AND LARGE FILE HANDLING
;
; Features:
; - GUI file picker (text files, BMP images, any file)
; - BMP header detection and preservation  
; - RGB 24-bit pixel-aware encoding
; - Grayscale 8-bit encoding - NOW FULLY IMPLEMENTED
; - Generic byte-by-byte for text files
; - Hybrid/Adaptive RLE (runs + literals)
; - RDTSC CPU cycle measurement
; - Full error handling
; - Comprehensive performance reporting
;
;============================================================================

INCLUDE Irvine32.inc
INCLUDELIB kernel32.lib
INCLUDELIB user32.lib
INCLUDELIB comdlg32.lib

;============================================================================
; STRUCTURES
;============================================================================

BITMAPFILEHEADER STRUCT
    bfType WORD ?
    bfSize DWORD ?
    bfReserved1 WORD ?
    bfReserved2 WORD ?
    bfOffBits DWORD ?
BITMAPFILEHEADER ENDS

BITMAPINFOHEADER STRUCT
    biSize DWORD ?
    biWidth DWORD ?
    biHeight DWORD ?
    biPlanes WORD ?
    biBitCount WORD ?
    biCompression DWORD ?
    biSizeImage DWORD ?
    biXPelsPerMeter DWORD ?
    biYPelsPerMeter DWORD ?
    biClrUsed DWORD ?
    biClrImportant DWORD ?
BITMAPINFOHEADER ENDS

OFN_STRUCT STRUCT
    lStructSize DWORD ?
    hwndOwner DWORD ?
    hInstance DWORD ?
    lpstrFilter DWORD ?
    lpstrCustomFilter DWORD ?
    nMaxCustFilter DWORD ?
    nFilterIndex DWORD ?
    lpstrFile DWORD ?
    nMaxFile DWORD ?
    lpstrFileTitle DWORD ?
    nMaxFileTitle DWORD ?
    lpstrInitialDir DWORD ?
    lpstrTitle DWORD ?
    Flags DWORD ?
    nFileOffset WORD ?
    nFileExtension WORD ?
    lpstrDefExt DWORD ?
    lCustData DWORD ?
    lpfnHook DWORD ?
    lpTemplateName DWORD ?
OFN_STRUCT ENDS

;============================================================================
; CONSTANTS
;============================================================================

MAX_PATH equ 260
OFN_FILEMUSTEXIST equ 1000h
OFN_PATHMUSTEXIST equ 800h
GENERIC_READ equ 80000000h
GENERIC_WRITE equ 40000000h
CREATE_ALWAYS equ 2
OPEN_EXISTING equ 3
FILE_ATTRIBUTE_NORMAL equ 80h
INVALID_HANDLE_VALUE equ -1
MAX_RUN equ 127
MAX_LITERAL equ 127
GMEM_FIXED equ 0000h
GMEM_ZEROINIT equ 0040h
MODE_GENERIC equ 0
MODE_RGB24 equ 1
MODE_GRAYSCALE equ 2
DECOMP_BUFFER_MULTIPLIER equ 100 ; Increased from 20 for large files
MIN_RUN_LENGTH equ 4
MAX_FILE_SIZE equ 100000000 ; 100MB limit for safety

;============================================================================
; EXTERNAL FUNCTIONS - Windows API
;============================================================================

GetOpenFileNameA PROTO :DWORD
GlobalAlloc PROTO :DWORD, :DWORD
GlobalFree PROTO :DWORD
GetFileSize PROTO :DWORD, :DWORD

;============================================================================
; DATA SECTION
;============================================================================

.data

; Menu
menu_text BYTE 13,10,"=== IMAGE-AWARE RLE ENCODER MENU ===",13,10
         BYTE "1. Select File",13,10
         BYTE "2. Encode File",13,10
         BYTE "3. Decode File",13,10
         BYTE "4. Exit",13,10,0

msgPressAnyKey BYTE 13,10,"Press any key to continue...",0
selectedFile BYTE 256 DUP(0)
isBMP BYTE 0

; GUI structures
ofn OFN_STRUCT <>
szFileName BYTE MAX_PATH DUP(0)
szFileTitle BYTE MAX_PATH DUP(0)

; File dialog filter
szFilter BYTE "All Files (*.*)", 0, "*.*", 0
         BYTE "Bitmap Images (*.bmp)", 0, "*.bmp", 0
         BYTE "Text Files (*.txt)", 0, "*.txt", 0
         BYTE 0

szDialogTitle BYTE "Select File to Encode", 0

; Output filenames
encodedFile BYTE MAX_PATH DUP(0)
decodedFile BYTE MAX_PATH DUP(0)
szEncExt BYTE ".rle", 0
szDecExt BYTE ".dec", 0

; Messages
msgWelcome BYTE "==============================================", 0dh, 0ah
          BYTE " IMAGE-AWARE Hybrid RLE Encoder", 0dh, 0ah
          BYTE " 32-bit MASM with Irvine32 Library", 0dh, 0ah
          BYTE "==============================================", 0dh, 0ah, 0

msgSelectFile BYTE "Opening file selection dialog...", 0dh, 0ah, 0
msgNoFile BYTE "No file selected. Exiting.", 0dh, 0ah, 0
msgProcessing BYTE "Processing file: ", 0
msgDetecting BYTE "Detecting file format...", 0dh, 0ah, 0
msgIsBMP BYTE "Detected: BMP Image ", 0
msgIsGeneric BYTE "Detected: Generic file (byte-by-byte mode)", 0dh, 0ah, 0
msgBitDepth BYTE "-bit", 0dh, 0ah, 0
msgDimensions BYTE "Image dimensions: ", 0
msgByText BYTE " x ", 0
msgPixelData BYTE "Pixel data size: ", 0
msgHeaderSize BYTE "Header size: ", 0
msgEncoding BYTE "Encoding with Hybrid RLE...", 0dh, 0ah, 0
msgDecoding BYTE "Decoding encoded data...", 0dh, 0ah, 0
msgWriting BYTE "Writing output files...", 0dh, 0ah, 0
msgComplete BYTE 0dh, 0ah, "=== Operation Complete! ===", 0dh, 0ah, 0
msgOrigSize BYTE "Original Size: ", 0
msgEncodedSize BYTE "Encoded Size: ", 0
msgDecodedSize BYTE "Decoded Size: ", 0
msgRatioText BYTE "Encoding Ratio: ", 0
msgCyclesText BYTE "CPU Cycles Used: ", 0
msgBytesText BYTE " bytes", 0dh, 0ah, 0
msgCyclesEnd BYTE " cycles", 0dh, 0ah, 0
msgRatioFormat BYTE ":1", 0dh, 0ah, 0
msgError BYTE "ERROR: ", 0
msgFileReadError BYTE "Could not read file!", 0dh, 0ah, 0
msgFileWriteError BYTE "Could not write file!", 0dh, 0ah, 0
msgMemError BYTE "Memory allocation failed!", 0dh, 0ah, 0
msgSavedEnc BYTE "Encoded file saved as: ", 0
msgSavedDec BYTE "Decoded file saved as: ", 0
msgNewline BYTE 0dh, 0ah, 0
msgVerifySuccess BYTE "Verification: Data integrity confirmed!", 0dh, 0ah, 0
msgVerifyFailed BYTE "WARNING: Decoded data does not match original!", 0dh, 0ah, 0
msgFileTooLarge BYTE "ERROR: File too large (max 100MB)", 0dh, 0ah, 0

; Menu messages
msgMenuTitle BYTE 0dh, 0ah
             BYTE "==============================================", 0dh, 0ah
             BYTE " MAIN MENU", 0dh, 0ah
             BYTE "==============================================", 0dh, 0ah, 0

msgMenuOption1 BYTE "1. Encode a file", 0dh, 0ah, 0
msgMenuOption2 BYTE "2. Decode a file", 0dh, 0ah, 0
msgMenuOption3 BYTE "3. Encode and verify", 0dh, 0ah, 0
msgMenuOption4 BYTE "4. View last encoding statistics", 0dh, 0ah, 0
msgMenuOption5 BYTE "5. Exit", 0dh, 0ah, 0

msgMenuPrompt BYTE 0dh, 0ah, "Enter your choice (1-5): ", 0
msgInvalidChoice BYTE "Invalid choice! Please enter 1-5.", 0dh, 0ah, 0
msgPressKey BYTE 0dh, 0ah, "Press any key to continue...", 0dh, 0ah, 0
msgNoStats BYTE "No encoding statistics available yet!", 0dh, 0ah, 0
msgDecodeOnly BYTE "Select an encoded (.rle) file to decode:", 0dh, 0ah, 0

; Menu state
menuChoice BYTE 0
hasStats DWORD 0

; Performance tracking
cyclesStart DWORD 0, 0
cyclesEnd DWORD 0, 0
totalCycles DWORD 0, 0
encodeCycles DWORD 0, 0
decodeCycles DWORD 0, 0

; File statistics
originalSize DWORD 0
encodedSize DWORD 0
decodedSize DWORD 0
headerSize DWORD 0
pixelDataSize DWORD 0

; Image info
imageWidth DWORD 0
imageHeight DWORD 0
bitDepth WORD 0
encodingMode DWORD MODE_GENERIC

; File handles
hInputFile DWORD ?
hEncFile DWORD ?
hDecFile DWORD ?
bytesReadWritten DWORD ?

; Buffer pointers
pInputBuffer DWORD ?
pEncodedBuffer DWORD ?
pOutputBuffer DWORD ?

;============================================================================
; CODE SECTION
;============================================================================

.code

;============================================================================
; MAIN PROCEDURE - Menu-driven version
;============================================================================

main PROC
menu_loop:
    call DisplayMenu
    mov al, menuChoice
    cmp al, 1
    je option_encode
    cmp al, 2
    je option_decode
    cmp al, 3
    je option_verify
    cmp al, 4
    je option_stats
    cmp al, 5
    je option_exit

option_encode:
    call ProcessEncode
    jmp menu_loop

option_decode:
    call ProcessDecode
    jmp menu_loop

option_verify:
    call ProcessEncodeAndVerify
    jmp menu_loop

option_stats:
    call ViewStatistics
    jmp menu_loop

option_exit:
    call Crlf
    mov edx, OFFSET msgComplete
    call WriteString
    call Cleanup
    INVOKE ExitProcess, 0
main ENDP

;============================================================================
; ReadTSC - Read Time Stamp Counter
; Returns: EDX:EAX = 64-bit cycle count
;============================================================================

ReadTSC PROC
    push ebx
    push ecx
    xor eax, eax
    cpuid
    rdtsc
    pop ecx
    pop ebx
    ret
ReadTSC ENDP

;============================================================================
; ShowFileDialog - Display Windows file open dialog
; Returns: EAX = 1 if file selected, 0 if cancelled
;============================================================================

ShowFileDialog PROC
    mov ofn.lStructSize, SIZEOF OFN_STRUCT
    mov ofn.hwndOwner, 0
    mov eax, OFFSET szFilter
    mov ofn.lpstrFilter, eax
    mov eax, OFFSET szFileName
    mov ofn.lpstrFile, eax
    mov ofn.nMaxFile, MAX_PATH
    mov eax, OFFSET szFileTitle
    mov ofn.lpstrFileTitle, eax
    mov ofn.nMaxFileTitle, MAX_PATH
    mov eax, OFFSET szDialogTitle
    mov ofn.lpstrTitle, eax
    mov ofn.Flags, OFN_FILEMUSTEXIST OR OFN_PATHMUSTEXIST
    mov edx, OFFSET msgSelectFile
    call WriteString
    INVOKE GetOpenFileNameA, ADDR ofn
    ret
ShowFileDialog ENDP

;============================================================================
; DetectFileFormat - Check if BMP and extract image info
;============================================================================

DetectFileFormat PROC
    LOCAL fileHeader:BITMAPFILEHEADER
    LOCAL infoHeader:BITMAPINFOHEADER

    mov esi, pInputBuffer

    ; Check BMP signature "BM" (0x4D42)
    mov ax, WORD PTR [esi]
    cmp ax, 4D42h
    jne not_bmp

    ; Copy file header
    lea edi, fileHeader
    mov ecx, SIZEOF BITMAPFILEHEADER
    rep movsb

    ; Copy info header
    mov esi, pInputBuffer
    add esi, SIZEOF BITMAPFILEHEADER
    lea edi, infoHeader
    mov ecx, SIZEOF BITMAPINFOHEADER
    rep movsb

    ; Extract image information
    mov eax, infoHeader.biWidth
    mov imageWidth, eax
    mov eax, infoHeader.biHeight
    mov imageHeight, eax
    mov ax, infoHeader.biBitCount
    mov bitDepth, ax

    ; Get header size (offset to pixel data)
    mov eax, fileHeader.bfOffBits
    mov headerSize, eax

    ; Calculate pixel data size
    mov eax, originalSize
    sub eax, headerSize
    mov pixelDataSize, eax

    ; Set encoding mode
    mov isBMP, 1
    cmp bitDepth, 24
    je set_rgb_mode
    cmp bitDepth, 8
    je set_grayscale_mode
    jmp set_generic_mode

set_rgb_mode:
    mov encodingMode, MODE_RGB24
    jmp display_info

set_grayscale_mode:
    mov encodingMode, MODE_GRAYSCALE
    jmp display_info

set_generic_mode:
    mov encodingMode, MODE_GENERIC
    jmp display_info

not_bmp:
    mov isBMP, 0
    mov encodingMode, MODE_GENERIC
    mov edx, OFFSET msgIsGeneric
    call WriteString
    ret

display_info:
    ; Display BMP information
    mov edx, OFFSET msgIsBMP
    call WriteString
    movzx eax, bitDepth
    call WriteDec
    mov edx, OFFSET msgBitDepth
    call WriteString
    mov edx, OFFSET msgDimensions
    call WriteString
    mov eax, imageWidth
    call WriteDec
    mov edx, OFFSET msgByText
    call WriteString
    mov eax, imageHeight
    call WriteDec
    call Crlf
    mov edx, OFFSET msgHeaderSize
    call WriteString
    mov eax, headerSize
    call WriteDec
    mov edx, OFFSET msgBytesText
    call WriteString
    mov edx, OFFSET msgPixelData
    call WriteString
    mov eax, pixelDataSize
    call WriteDec
    mov edx, OFFSET msgBytesText
    call WriteString
    ret
DetectFileFormat ENDP

;============================================================================
; BuildOutputNames - Create output filenames
;============================================================================

BuildOutputNames PROC
    push esi
    push edi
    push ecx

    ; Build encoded filename
    mov esi, OFFSET szFileName
    mov edi, OFFSET encodedFile
    mov ecx, MAX_PATH
copy_name1:
    lodsb
    stosb
    test al, al
    loopnz copy_name1

    ; Find end of string
    mov edi, OFFSET encodedFile
find_end1:
    cmp BYTE PTR [edi], 0
    je found_end1
    inc edi
    jmp find_end1

found_end1:
    ; Append .rle
    mov esi, OFFSET szEncExt
append_ext1:
    lodsb
    stosb
    test al, al
    jnz append_ext1

    ; Build decoded filename
    mov esi, OFFSET szFileName
    mov edi, OFFSET decodedFile
    mov ecx, MAX_PATH
copy_name2:
    lodsb
    stosb
    test al, al
    loopnz copy_name2

    mov edi, OFFSET decodedFile
find_end2:
    cmp BYTE PTR [edi], 0
    je found_end2
    inc edi
    jmp find_end2

found_end2:
    mov esi, OFFSET szDecExt
append_ext2:
    lodsb
    stosb
    test al, al
    jnz append_ext2

    pop ecx
    pop edi
    pop esi
    ret
BuildOutputNames ENDP

;============================================================================
; ReadInputFile - Read file into memory
; Returns: EAX = 1 if success, 0 if error
;============================================================================

ReadInputFile PROC
    LOCAL fileSize:DWORD

    INVOKE CreateFileA, ADDR szFileName, GENERIC_READ, 0, NULL,
                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
    cmp eax, INVALID_HANDLE_VALUE
    je read_error
    mov hInputFile, eax

    INVOKE GetFileSize, hInputFile, NULL
    cmp eax, -1
    je read_error
    
    ; Check file size limit
    cmp eax, MAX_FILE_SIZE
    ja file_too_large
    
    mov originalSize, eax
    mov fileSize, eax

    INVOKE GlobalAlloc, GMEM_FIXED, fileSize
    test eax, eax
    jz read_error
    mov pInputBuffer, eax

    INVOKE ReadFile, hInputFile, pInputBuffer, fileSize,
                    ADDR bytesReadWritten, NULL
    test eax, eax
    jz read_error

    INVOKE CloseHandle, hInputFile
    mov eax, 1
    ret

file_too_large:
    mov edx, OFFSET msgFileTooLarge
    call WriteString
    INVOKE CloseHandle, hInputFile
    xor eax, eax
    ret

read_error:
    xor eax, eax
    ret
ReadInputFile ENDP

;============================================================================
; WriteEncodedFile - Write encoded data to file
; Returns: EAX = 1 if success, 0 if error
;============================================================================

WriteEncodedFile PROC
    INVOKE CreateFileA, ADDR encodedFile, GENERIC_WRITE, 0, NULL,
                        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
    cmp eax, INVALID_HANDLE_VALUE
    je write_error
    mov hEncFile, eax

    INVOKE WriteFile, hEncFile, pEncodedBuffer, encodedSize,
                    ADDR bytesReadWritten, NULL
    test eax, eax
    jz write_error

    INVOKE CloseHandle, hEncFile
    mov eax, 1
    ret

write_error:
    xor eax, eax
    ret
WriteEncodedFile ENDP

;============================================================================
; WriteDecodedFile - Write decoded data to file
; Returns: EAX = 1 if success, 0 if error
;============================================================================

WriteDecodedFile PROC
    INVOKE CreateFileA, ADDR decodedFile, GENERIC_WRITE, 0, NULL,
                        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
    cmp eax, INVALID_HANDLE_VALUE
    je write_error2
    mov hDecFile, eax

    INVOKE WriteFile, hDecFile, pOutputBuffer, decodedSize,
                    ADDR bytesReadWritten, NULL
    test eax, eax
    jz write_error2

    INVOKE CloseHandle, hDecFile
    mov eax, 1
    ret

write_error2:
    xor eax, eax
    ret
WriteDecodedFile ENDP

;============================================================================
; VerifyData - Compare original and decoded data
;============================================================================

VerifyData PROC
    push esi
    push edi
    push ecx

    ; Check if sizes match
    mov eax, originalSize
    cmp eax, decodedSize
    jne verify_failed

    ; Compare byte by byte
    mov esi, pInputBuffer
    mov edi, pOutputBuffer
    mov ecx, originalSize
    repe cmpsb
    jne verify_failed

    ; Success
    mov edx, OFFSET msgVerifySuccess
    call WriteString
    jmp verify_done

verify_failed:
    mov edx, OFFSET msgVerifyFailed
    call WriteString

verify_done:
    pop ecx
    pop edi
    pop esi
    ret
VerifyData ENDP

;============================================================================
; EncodeRLE_Image - Encode BMP image with header preservation
; Parameters: [ebp+8] = header size
;             [ebp+12] = input buffer
;             [ebp+16] = pixel data size
;             [ebp+20] = output buffer
; Returns: EAX = total encoded size
;============================================================================

EncodeRLE_Image PROC
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi

    mov esi, [ebp+12] ; Input buffer
    mov edi, [ebp+20] ; Output buffer
    mov eax, [ebp+8]  ; Header size
    xor edx, edx      ; Output position

    ; Copy header unchanged
    push ecx
    mov ecx, eax
    mov edx, 0
copy_header_enc:
    mov al, [esi]
    mov [edi], al
    inc esi
    inc edi
    inc edx
    loop copy_header_enc
    pop ecx

    ; Encode pixel data
    mov ecx, [ebp+16] ; Pixel data size
    
    cmp encodingMode, MODE_RGB24
    je encode_rgb24_img
    cmp encodingMode, MODE_GRAYSCALE
    je encode_grayscale_img

    ; Generic encoding
    push edx
    push edi
    push ecx
    push esi
    call EncodeRLE_Generic
    pop edx
    add eax, edx
    jmp encode_img_done

encode_rgb24_img:
    push edx
    push edi
    push ecx
    push esi
    call EncodeRLE_RGB24
    pop edx
    add eax, edx
    jmp encode_img_done

encode_grayscale_img:
    push edx
    push edi
    ; For grayscale, convert byte size to pixel count
    mov eax, ecx
    push eax
    push esi
    call EncodeRLE_Grayscale
    pop edx
    add eax, edx

encode_img_done:
    pop edi
    pop esi
    pop ebx
    pop ebp
    ret 16
EncodeRLE_Image ENDP

;============================================================================
; EncodeRLE_RGB24 - Encode 24-bit RGB pixels
; Parameters: [ebp+8] = pixel data pointer
;             [ebp+12] = pixel data size
;             [ebp+16] = output buffer
; Returns: EAX = encoded size
;============================================================================

EncodeRLE_RGB24 PROC
    push ebp
    mov ebp, esp
    sub esp, 12
    push ebx
    push esi
    push edi

    mov esi, [ebp+8]
    mov edi, [ebp+16]
    mov ecx, [ebp+12]
    xor edx, edx

    mov eax, ecx
    mov ebx, 3
    div ebx
    mov ecx, eax
    xor edx, edx
    xor ebx, ebx

encode_rgb_loop:
    cmp ebx, ecx
    jge encode_rgb_done

    ; Read current RGB pixel
    mov eax, ebx
    imul eax, 3
    mov al, [esi + eax]
    mov [ebp-4], al
    mov al, [esi + eax + 1]
    mov [ebp-3], al
    mov al, [esi + eax + 2]
    mov [ebp-2], al
    mov DWORD PTR [ebp-8], 1

count_rgb_run:
    mov eax, ebx
    add eax, [ebp-8]
    cmp eax, ecx
    jge check_rgb_type
    cmp DWORD PTR [ebp-8], MAX_RUN
    jge check_rgb_type

    ; Compare next pixel
    mov eax, ebx
    add eax, [ebp-8]
    imul eax, 3
    mov al, [esi + eax]
    cmp al, [ebp-4]
    jne check_rgb_type
    mov al, [esi + eax + 1]
    cmp al, [ebp-3]
    jne check_rgb_type
    mov al, [esi + eax + 2]
    cmp al, [ebp-2]
    jne check_rgb_type
    inc DWORD PTR [ebp-8]
    jmp count_rgb_run

check_rgb_type:
    cmp DWORD PTR [ebp-8], 4
    jge encode_rgb_as_run

    ; Collect literals
    mov DWORD PTR [ebp-8], 1
collect_rgb_literals:
    mov eax, ebx
    add eax, [ebp-8]
    cmp eax, ecx
    jge encode_rgb_literals
    cmp DWORD PTR [ebp-8], MAX_LITERAL
    jge encode_rgb_literals
    inc DWORD PTR [ebp-8]
    jmp collect_rgb_literals

encode_rgb_literals:
    ; Negative control byte
    mov al, BYTE PTR [ebp-8]
    neg al
    mov [edi + edx], al
    inc edx

    ; Copy literal pixels
    push ecx
    mov ecx, [ebp-8]
copy_rgb_lit:
    mov eax, ebx
    imul eax, 3
    mov al, [esi + eax]
    mov [edi + edx], al
    inc edx
    mov al, [esi + eax + 1]
    mov [edi + edx], al
    inc edx
    mov al, [esi + eax + 2]
    mov [edi + edx], al
    inc edx
    inc ebx
    loop copy_rgb_lit
    pop ecx
    jmp encode_rgb_loop

encode_rgb_as_run:
    ; Positive control byte
    mov al, BYTE PTR [ebp-8]
    mov [edi + edx], al
    inc edx

    ; Write RGB pixel
    mov al, [ebp-4]
    mov [edi + edx], al
    inc edx
    mov al, [ebp-3]
    mov [edi + edx], al
    inc edx
    mov al, [ebp-2]
    mov [edi + edx], al
    inc edx

    mov eax, [ebp-8]
    add ebx, eax
    jmp encode_rgb_loop

encode_rgb_done:
    mov eax, edx
    pop edi
    pop esi
    pop ebx
    add esp, 12
    pop ebp
    ret 12
EncodeRLE_RGB24 ENDP

;============================================================================
; EncodeRLE_Grayscale - Encode 8-bit grayscale pixels
; Parameters: [ebp+8] = pixel data pointer
;             [ebp+12] = pixel count
;             [ebp+16] = output buffer
; Returns: EAX = encoded size
;============================================================================

EncodeRLE_Grayscale PROC
    push ebp
    mov ebp, esp
    sub esp, 12
    push ebx
    push esi
    push edi

    mov esi, [ebp+8]      ; Pixel data (1 byte per pixel)
    mov edi, [ebp+16]     ; Output buffer
    mov ecx, [ebp+12]     ; Pixel count
    xor edx, edx          ; Output position
    xor ebx, ebx          ; Input pixel index

encode_gray_loop:
    cmp ebx, ecx
    jge encode_gray_done

    ; Get current grayscale value
    mov al, [esi+ebx]
    mov BYTE PTR [ebp-1], al
    mov DWORD PTR [ebp-5], 1   ; Run count

    ; Count consecutive identical pixels
gray_count_run:
    inc ebx
    cmp ebx, ecx
    jge gray_check_type
    cmp DWORD PTR [ebp-5], MAX_RUN
    jge gray_check_type
    mov al, [esi+ebx]
    cmp al, BYTE PTR [ebp-1]
    jne gray_check_type
    inc DWORD PTR [ebp-5]
    jmp gray_count_run

gray_check_type:
    ; Decide: Run vs Literal encoding
    cmp DWORD PTR [ebp-5], MIN_RUN_LENGTH
    jae encode_gray_run

    ; Collect literals with lookahead
    mov DWORD PTR [ebp-5], 1
    mov DWORD PTR [ebp-9], ebx

gray_collect_literals:
    cmp ebx, ecx
    jge encode_gray_literals
    cmp DWORD PTR [ebp-5], MAX_LITERAL
    jge encode_gray_literals

    ; Look ahead for potential runs
    mov al, [esi+ebx]
    mov BYTE PTR [ebp-2], 1
    push ebx
    inc ebx

gray_lookahead:
    cmp ebx, ecx
    jae gray_no_run
    cmp BYTE PTR [ebp-2], 4
    jae gray_found_run
    mov ah, [esi+ebx]
    cmp ah, al
    jne gray_no_run
    inc BYTE PTR [ebp-2]
    inc ebx
    jmp gray_lookahead

gray_found_run:
    pop ebx
    jmp encode_gray_literals

gray_no_run:
    pop ebx
    inc DWORD PTR [ebp-5]
    inc ebx
    jmp gray_collect_literals

encode_gray_literals:
    ; Encode as literal sequence
    mov al, BYTE PTR [ebp-5]
    neg al
    mov [edi+edx], al
    inc edx

    ; Copy literal pixels
    push ecx
    mov ecx, DWORD PTR [ebp-5]
    mov ebx, DWORD PTR [ebp-9]

gray_copy_lit:
    mov al, [esi+ebx]
    mov [edi+edx], al
    inc ebx
    inc edx
    loop gray_copy_lit
    pop ecx
    jmp encode_gray_loop

encode_gray_run:
    ; Encode as run
    mov al, BYTE PTR [ebp-5]
    mov [edi+edx], al
    inc edx
    mov al, BYTE PTR [ebp-1]
    mov [edi+edx], al
    inc edx

    ; Advance input position
    mov eax, DWORD PTR [ebp-5]
    add ebx, eax
    jmp encode_gray_loop

encode_gray_done:
    mov eax, edx
    pop edi
    pop esi
    pop ebx
    add esp, 12
    pop ebp
    ret 12
EncodeRLE_Grayscale ENDP

;============================================================================
; EncodeRLE_Generic - Generic byte-by-byte encoding (SAFE VERSION)
; Parameters: [ebp+8] = input buffer
;             [ebp+12] = input size
;             [ebp+16] = output buffer
; Returns: EAX = encoded size
;============================================================================

EncodeRLE_Generic PROC
    push ebp
    mov ebp, esp
    sub esp, 12
    push ebx
    push esi
    push edi

    mov esi, [ebp+8]
    mov ecx, [ebp+12]
    mov edi, [ebp+16]
    xor edx, edx
    xor ebx, ebx

encode_gen_loop:
    cmp ebx, ecx
    jae encode_gen_done

    ; Get current byte
    mov al, [esi+ebx]
    mov BYTE PTR [ebp-1], al
    mov BYTE PTR [ebp-2], 1

    ; Count consecutive matching bytes
    push ebx
    inc ebx
count_run:
    cmp ebx, ecx
    jae run_done
    movzx eax, BYTE PTR [ebp-2]
    cmp eax, MAX_RUN
    jae run_done
    mov al, [esi+ebx]
    cmp al, BYTE PTR [ebp-1]
    jne run_done
    inc BYTE PTR [ebp-2]
    inc ebx
    jmp count_run
run_done:
    pop ebx

    ; If run >= 4, encode as RLE
    cmp BYTE PTR [ebp-2], 4
    jae encode_as_run

    ; Collect literals
    mov BYTE PTR [ebp-2], 0
    mov DWORD PTR [ebp-6], ebx

collect_literals:
    cmp ebx, ecx
    jae write_literals
    movzx eax, BYTE PTR [ebp-2]
    cmp eax, MAX_LITERAL
    jae write_literals

    ; Look ahead for runs of 4+
    mov al, [esi+ebx]
    mov BYTE PTR [ebp-8], 1
    push ebx
    inc ebx
lookahead:
    cmp ebx, ecx
    jae no_run_ahead
    cmp BYTE PTR [ebp-8], 4
    jae found_run_ahead
    mov ah, [esi+ebx]
    cmp ah, al
    jne no_run_ahead
    inc BYTE PTR [ebp-8]
    inc ebx
    jmp lookahead

found_run_ahead:
    pop ebx
    jmp write_literals

no_run_ahead:
    pop ebx
    inc BYTE PTR [ebp-2]
    inc ebx
    jmp collect_literals

write_literals:
    ; Ensure we have literals to write
    cmp BYTE PTR [ebp-2], 0
    je encode_gen_loop

    ; Write control byte (negative)
    mov al, BYTE PTR [ebp-2]
    neg al
    mov [edi+edx], al
    inc edx

    ; Copy literal bytes
    push ecx
    movzx ecx, BYTE PTR [ebp-2]
    mov ebx, DWORD PTR [ebp-6]
copy_lit:
    mov al, [esi+ebx]
    mov [edi+edx], al
    inc ebx
    inc edx
    loop copy_lit
    pop ecx
    jmp encode_gen_loop

encode_as_run:
    ; Write control byte (positive)
    mov al, BYTE PTR [ebp-2]
    mov [edi+edx], al
    inc edx

    ; Write run value
    mov al, BYTE PTR [ebp-1]
    mov [edi+edx], al
    inc edx

    ; Advance input position
    movzx eax, BYTE PTR [ebp-2]
    add ebx, eax
    jmp encode_gen_loop

encode_gen_done:
    mov eax, edx
    pop edi
    pop esi
    pop ebx
    add esp, 12
    pop ebp
    ret 12
EncodeRLE_Generic ENDP

;============================================================================
; DecodeRLE_Image - Decode BMP image with header preservation
; Parameters: [ebp+8] = header size
;             [ebp+12] = encoded buffer
;             [ebp+16] = encoded size
;             [ebp+20] = output buffer
; Returns: EAX = decoded size
;============================================================================

DecodeRLE_Image PROC
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi

    mov esi, [ebp+12]
    mov edi, [ebp+20]
    mov eax, [ebp+8]

    ; Copy header unchanged
    push ecx
    mov ecx, eax
    xor edx, edx
copy_header_dec:
    mov al, [esi]
    mov [edi], al
    inc esi
    inc edi
    inc edx
    loop copy_header_dec
    pop ecx

    ; Decode pixel data
    mov ecx, [ebp+16]
    sub ecx, [ebp+8]
    
    cmp encodingMode, MODE_RGB24
    je decode_rgb24_img
    cmp encodingMode, MODE_GRAYSCALE
    je decode_grayscale_img

    ; Generic decoding
    push edx
    push edi
    push ecx
    push esi
    call DecodeRLE_Generic
    pop edx
    add eax, edx
    jmp decode_img_done

decode_rgb24_img:
    push edx
    push edi
    push ecx
    push esi
    call DecodeRLE_RGB24
    pop edx
    add eax, edx
    jmp decode_img_done

decode_grayscale_img:
    push edx
    push edi
    push ecx
    push esi
    call DecodeRLE_Grayscale
    pop edx
    add eax, edx

decode_img_done:
    pop edi
    pop esi
    pop ebx
    pop ebp
    ret 16
DecodeRLE_Image ENDP

;============================================================================
; DecodeRLE_RGB24 - Decode 24-bit RGB pixels (FIXED VERSION)
; Parameters: [ebp+8] = encoded buffer
;             [ebp+12] = encoded size  
;             [ebp+16] = output buffer
; Returns: EAX = decoded size
;============================================================================

DecodeRLE_RGB24 PROC
    push ebp
    mov ebp, esp
    sub esp, 4                ; Local: [ebp-1]=B, [ebp-2]=G, [ebp-3]=R
    push ebx
    push esi
    push edi
    
    mov esi, [ebp+8]          ; Encoded buffer
    mov edi, [ebp+16]         ; Output buffer
    mov ecx, [ebp+12]         ; Encoded size
    xor edx, edx              ; Output position
    xor ebx, ebx              ; Input position

decode_rgb_loop:
    cmp ebx, ecx
    jge decode_rgb_done
    
    ; BOUNDS CHECK - ensure we have at least 1 byte
    mov eax, ebx
    inc eax
    cmp eax, ecx
    jg decode_rgb_done
    
    ; READ CONTROL BYTE
    movsx eax, BYTE PTR [esi+ebx]
    inc ebx
    
    test eax, eax
    jns decode_rgb_run        ; Positive = run
    
    ; NEGATIVE = LITERAL RGB PIXELS
    neg eax                   ; Get literal count
    
    ; BOUNDS CHECK - ensure we have enough bytes for literals
    push eax
    mov eax, ebx
    add eax, eax              ; ×2
    add eax, [esp]            ; + literal count
    add eax, [esp]            ; + literal count again (×3 total)
    cmp eax, ecx
    pop eax
    jg decode_rgb_done
    
    push ecx
    mov ecx, eax              ; Number of pixels
    
decode_rgb_lit_loop:
    ; BOUNDS CHECK for each pixel
    mov eax, ebx
    add eax, 2
    cmp eax, [ebp+12]         ; Compare with original encoded size
    jg decode_rgb_lit_done
    
    ; COPY RGB TRIPLET - preserve BGR order
    mov al, [esi+ebx]         ; Read B
    mov [edi+edx], al
    inc ebx
    inc edx
    mov al, [esi+ebx]         ; Read G
    mov [edi+edx], al
    inc ebx  
    inc edx
    mov al, [esi+ebx]         ; Read R
    mov [edi+edx], al
    inc ebx
    inc edx
    loop decode_rgb_lit_loop
    
decode_rgb_lit_done:
    pop ecx
    jmp decode_rgb_loop

decode_rgb_run:
    ; POSITIVE = RGB RUN
    
    ; BOUNDS CHECK - ensure we have 3 bytes for RGB value
    mov eax, ebx
    add eax, 3
    cmp eax, [ebp+12]         ; Compare with original encoded size
    jg decode_rgb_done
    
    push ecx
    mov ecx, eax              ; Run length
    
    ; READ RGB PIXEL VALUE ONCE
    mov al, [esi+ebx]         ; Read B
    mov [ebp-1], al
    mov al, [esi+ebx+1]       ; Read G
    mov [ebp-2], al  
    mov al, [esi+ebx+2]       ; Read R
    mov [ebp-3], al
    add ebx, 3                ; Skip the RGB value
    
    ; REPLICATE RGB PIXEL - CORRECT BGR ORDER
decode_rgb_run_loop:
    mov al, [ebp-1]           ; Write B
    mov [edi+edx], al
    inc edx
    mov al, [ebp-2]           ; Write G
    mov [edi+edx], al
    inc edx
    mov al, [ebp-3]           ; Write R
    mov [edi+edx], al
    inc edx
    loop decode_rgb_run_loop
    
    pop ecx
    jmp decode_rgb_loop

decode_rgb_done:
    mov eax, edx              ; Return decoded size (in bytes)
    pop edi
    pop esi
    pop ebx
    add esp, 4
    pop ebp
    ret 12
DecodeRLE_RGB24 ENDP

;============================================================================
; DecodeRLE_Grayscale - Decode 8-bit grayscale pixels  
; Parameters: [ebp+8] = encoded buffer
;             [ebp+12] = encoded size
;             [ebp+16] = output buffer
; Returns: EAX = decoded size (in bytes)
;============================================================================

DecodeRLE_Grayscale PROC
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi
    
    mov esi, [ebp+8]          ; Encoded data
    mov edi, [ebp+16]         ; Output buffer
    mov ecx, [ebp+12]         ; Encoded size
    xor edx, edx              ; Output position
    xor ebx, ebx              ; Input position
    
decode_gray_loop:
    cmp ebx, ecx
    jge decode_gray_done
    
    ; BOUNDS CHECK
    cmp ebx, ecx
    jge decode_gray_done
    
    ; READ CONTROL BYTE
    movsx eax, BYTE PTR [esi+ebx]
    inc ebx
    
    test eax, eax
    jns decode_gray_run        ; Positive = run
    
    ; NEGATIVE = LITERALS
    neg eax                   ; Get literal count
    
    ; BOUNDS CHECK FOR LITERALS
    push eax
    add eax, ebx
    cmp eax, ecx
    pop eax
    jg decode_gray_done
    
    ; COPY LITERAL BYTES
    push ecx
    mov ecx, eax
    
decode_gray_lit_loop:
    mov al, [esi+ebx]         ; Read literal byte
    mov [edi+edx], al         ; Write to output
    inc ebx
    inc edx
    loop decode_gray_lit_loop
    pop ecx
    jmp decode_gray_loop
    
decode_gray_run:
    ; POSITIVE = RUN
    
    ; BOUNDS CHECK
    cmp ebx, ecx
    jge decode_gray_done
    
    push ecx
    mov ecx, eax
    mov al, [esi+ebx]         ; Read value to repeat
    inc ebx
    
decode_gray_run_loop:
    mov [edi+edx], al         ; Write repeated value
    inc edx
    loop decode_gray_run_loop
    pop ecx
    jmp decode_gray_loop

decode_gray_done:
    mov eax, edx              ; Return decoded size
    pop edi
    pop esi
    pop ebx
    pop ebp
    ret 12
DecodeRLE_Grayscale ENDP

;============================================================================
; DecodeRLE_Generic - Generic byte-by-byte decoding (ENHANCED)
; Parameters: [ebp+8] = encoded buffer
;             [ebp+12] = encoded size
;             [ebp+16] = output buffer  
; Returns: EAX = decoded size
;============================================================================

DecodeRLE_Generic PROC
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi
    
    mov esi, [ebp+8]         ; Encoded buffer
    mov edi, [ebp+16]        ; Output buffer
    mov ecx, [ebp+12]        ; Encoded size
    xor edx, edx             ; Output position
    xor ebx, ebx             ; Input position

decode_gen_loop:
    cmp ebx, ecx             ; Check if processed all encoded bytes
    jge decode_gen_done
    
    ; BOUNDS CHECK - ensure we have control byte
    cmp ebx, ecx
    jge decode_gen_done
    
    ; READ CONTROL BYTE
    movsx eax, BYTE PTR [esi+ebx]
    inc ebx
    
    test eax, eax
    jns decode_gen_run        ; Positive = run
    
    ; NEGATIVE CONTROL BYTE = LITERALS
    neg eax                   ; Convert to positive count
    
    ; ENHANCED BOUNDS CHECK FOR LITERALS
    push eax
    mov eax, ebx
    add eax, [esp]            ; Current pos + literal count
    cmp eax, ecx
    pop eax
    jg decode_gen_done        ; Error - out of bounds
    
    ; COPY LITERAL BYTES
    push ecx
    mov ecx, eax              ; Set loop counter to literal count
    
decode_gen_lit_loop:
    ; Additional bounds check for each literal
    cmp ebx, [ebp+12]
    jge decode_gen_lit_done
    mov al, [esi+ebx]         ; Read literal byte
    mov [edi+edx], al         ; Write to output
    inc ebx                   ; Advance input
    inc edx                   ; Advance output
    loop decode_gen_lit_loop
    
decode_gen_lit_done:
    pop ecx
    jmp decode_gen_loop

decode_gen_run:
    ; POSITIVE CONTROL BYTE = RUN
    
    ; BOUNDS CHECK - ensure we have value byte
    cmp ebx, [ebp+12]
    jge decode_gen_done
    
    push ecx
    mov ecx, eax              ; Set loop counter to run length
    mov al, [esi+ebx]         ; Read value to repeat
    inc ebx                   ; Move past value byte
    
decode_gen_run_loop:
    mov [edi+edx], al         ; Write repeated value
    inc edx                   ; Advance output
    loop decode_gen_run_loop
    
    pop ecx
    jmp decode_gen_loop

decode_gen_done:
    mov eax, edx              ; Return decoded size
    pop edi
    pop esi
    pop ebx
    pop ebp
    ret 12
DecodeRLE_Generic ENDP

;============================================================================
; RemoveRLEExtension - Remove .rle from filename
;============================================================================

RemoveRLEExtension PROC
    push esi
    push edi
    push ecx
    push ebx

    mov esi, OFFSET szFileName
    mov edi, OFFSET decodedFile
    xor ecx, ecx
    xor ebx, ebx

copy_loop:
    mov al, [esi + ecx]
    mov [edi + ecx], al
    cmp al, '.'
    jne not_dot
    mov ebx, ecx
not_dot:
    test al, al
    jz check_extension
    inc ecx
    jmp copy_loop

check_extension:
    test ebx, ebx
    jz no_extension

    mov al, [edi + ebx + 1]
    or al, 20h
    cmp al, 'r'
    jne no_extension
    mov al, [edi + ebx + 2]
    or al, 20h
    cmp al, 'l'
    jne no_extension
    mov al, [edi + ebx + 3]
    or al, 20h
    cmp al, 'e'
    jne no_extension
    mov al, [edi + ebx + 4]
    test al, al
    jnz no_extension

    mov BYTE PTR [edi + ebx], 0
    jmp remove_done

no_extension:
remove_done:
    pop ebx
    pop ecx
    pop edi
    pop esi
    ret
RemoveRLEExtension ENDP

;============================================================================
; DisplayReport - Show comprehensive performance statistics
;============================================================================

DisplayReport PROC
    ; Original size
    mov edx, OFFSET msgOrigSize
    call WriteString
    mov eax, originalSize
    call WriteDec
    mov edx, OFFSET msgBytesText
    call WriteString

    ; Encoded size
    mov edx, OFFSET msgEncodedSize
    call WriteString
    mov eax, encodedSize
    call WriteDec
    mov edx, OFFSET msgBytesText
    call WriteString

    ; Decoded size
    mov edx, OFFSET msgDecodedSize
    call WriteString
    mov eax, decodedSize
    call WriteDec
    mov edx, OFFSET msgBytesText
    call WriteString

    ; Encoding ratio
    mov edx, OFFSET msgRatioText
    call WriteString
    mov ebx, encodedSize
    test ebx, ebx
    jz skip_ratio
    mov eax, originalSize
    xor edx, edx
    div ebx
    call WriteDec
    mov edx, OFFSET msgRatioFormat
    call WriteString
    jmp ratio_done

skip_ratio:
    mov edx, OFFSET msgRatioFormat
    call WriteString

ratio_done:
    ; CPU cycles
    mov edx, OFFSET msgCyclesText
    call WriteString
    mov eax, totalCycles
    call WriteDec
    mov edx, OFFSET msgCyclesEnd
    call WriteString

    ; Output file information
    call Crlf
    mov edx, OFFSET msgSavedEnc
    call WriteString
    mov edx, OFFSET encodedFile
    call WriteString
    call Crlf
    mov edx, OFFSET msgSavedDec
    call WriteString
    mov edx, OFFSET decodedFile
    call WriteString
    call Crlf
    ret
DisplayReport ENDP

;============================================================================
; DisplayMenu - Shows the main menu and gets user choice
; Returns: AL = user's choice (1-5)
;============================================================================

DisplayMenu PROC
    push edx

display_menu_loop:
    call Clrscr
    mov edx, OFFSET msgWelcome
    call WriteString
    mov edx, OFFSET msgMenuTitle
    call WriteString
    mov edx, OFFSET msgMenuOption1
    call WriteString
    mov edx, OFFSET msgMenuOption2
    call WriteString
    mov edx, OFFSET msgMenuOption3
    call WriteString
    mov edx, OFFSET msgMenuOption4
    call WriteString
    mov edx, OFFSET msgMenuOption5
    call WriteString

    mov edx, OFFSET msgMenuPrompt
    call WriteString
    call ReadChar
    call WriteChar
    call Crlf

    cmp al, '1'
    jb invalid_input
    cmp al, '5'
    ja invalid_input

    sub al, '0'
    mov menuChoice, al
    pop edx
    ret

invalid_input:
    mov edx, OFFSET msgInvalidChoice
    call WriteString
    mov edx, OFFSET msgPressKey
    call WriteString
    call ReadChar
    jmp display_menu_loop
DisplayMenu ENDP

;============================================================================
; ProcessEncode - Handle file encoding
;============================================================================

ProcessEncode PROC
    call ShowFileDialog
    test eax, eax
    jz no_file_encode

    mov edx, OFFSET msgProcessing
    call WriteString
    mov edx, OFFSET szFileName
    call WriteString
    call Crlf

    call ReadInputFile
    test eax, eax
    jz file_error_encode

    mov edx, OFFSET msgDetecting
    call WriteString
    call DetectFileFormat

    ; Allocate encoding buffer with safety margin
    mov eax, originalSize
    add eax, 10000h           ; Add 64KB safety margin
    INVOKE GlobalAlloc, GMEM_FIXED, eax
    test eax, eax
    jz mem_error_encode
    mov pEncodedBuffer, eax

    call BuildOutputNames
    call Crlf

    mov edx, OFFSET msgEncoding
    call WriteString
    call ReadTSC
    mov cyclesStart, eax
    mov cyclesStart+4, edx

    cmp isBMP, 1
    je encode_image_proc

    push pEncodedBuffer
    push originalSize
    push pInputBuffer
    call EncodeRLE_Generic
    jmp encoding_done_proc

encode_image_proc:
    push pEncodedBuffer
    push pixelDataSize
    push pInputBuffer
    push headerSize
    call EncodeRLE_Image

encoding_done_proc:
    mov encodedSize, eax
    call ReadTSC
    mov cyclesEnd, eax
    mov cyclesEnd+4, edx
    mov eax, cyclesEnd
    sub eax, cyclesStart
    mov encodeCycles, eax
    mov eax, cyclesEnd+4
    sbb eax, cyclesStart+4
    mov encodeCycles+4, eax

    mov edx, OFFSET msgWriting
    call WriteString
    call WriteEncodedFile
    test eax, eax
    jz write_error_encode

    mov hasStats, 1
    mov edx, OFFSET msgComplete
    call WriteString
    call Crlf
    mov edx, OFFSET msgOrigSize
    call WriteString
    mov eax, originalSize
    call WriteDec
    mov edx, OFFSET msgBytesText
    call WriteString
    mov edx, OFFSET msgEncodedSize
    call WriteString
    mov eax, encodedSize
    call WriteDec
    mov edx, OFFSET msgBytesText
    call WriteString
    mov edx, OFFSET msgSavedEnc
    call WriteString
    mov edx, OFFSET encodedFile
    call WriteString
    call Crlf
    jmp cleanup_encode

no_file_encode:
    mov edx, OFFSET msgNoFile
    call WriteString
    jmp encode_done

file_error_encode:
    mov edx, OFFSET msgError
    call WriteString
    mov edx, OFFSET msgFileReadError
    call WriteString
    jmp cleanup_encode

mem_error_encode:
    mov edx, OFFSET msgError
    call WriteString
    mov edx, OFFSET msgMemError
    call WriteString
    jmp cleanup_encode

write_error_encode:
    mov edx, OFFSET msgError
    call WriteString
    mov edx, OFFSET msgFileWriteError
    call WriteString

cleanup_encode:
    cmp pInputBuffer, 0
    je skip_cleanup_input_enc
    INVOKE GlobalFree, pInputBuffer
    mov pInputBuffer, 0
skip_cleanup_input_enc:
    cmp pEncodedBuffer, 0
    je skip_cleanup_enc
    INVOKE GlobalFree, pEncodedBuffer
    mov pEncodedBuffer, 0
skip_cleanup_enc:

encode_done:
    mov edx, OFFSET msgPressKey
    call WriteString
    call ReadChar
    ret
ProcessEncode ENDP

;============================================================================
; ProcessDecode - Handle file decoding (FIXED)
;============================================================================

ProcessDecode PROC
    mov edx, OFFSET msgDecodeOnly
    call WriteString

    call ShowFileDialog
    test eax, eax
    jz no_file_decode

    call ReadInputFile
    test eax, eax
    jz file_error_decode

    mov eax, originalSize
    mov encodedSize, eax

    ; Allocate output buffer with large safety multiplier
    mov eax, originalSize
    mov ebx, DECOMP_BUFFER_MULTIPLIER  ; Now 100x for large files
    mul ebx
    jc mem_error_decode
    INVOKE GlobalAlloc, GMEM_FIXED OR GMEM_ZEROINIT, eax
    test eax, eax
    jz mem_error_decode
    mov pOutputBuffer, eax

    ; Detect if this is a BMP by checking header
    mov esi, pInputBuffer
    mov ax, WORD PTR [esi]
    cmp ax, 4D42h
    jne decomp_generic

    mov isBMP, 1
    add esi, 10
    mov eax, DWORD PTR [esi]
    mov headerSize, eax
    mov esi, pInputBuffer
    add esi, SIZEOF BITMAPFILEHEADER + 14
    mov ax, WORD PTR [esi]
    mov bitDepth, ax

    cmp ax, 24
    je set_rgb_decode
    cmp ax, 8
    je set_gray_decode
    mov encodingMode, MODE_GENERIC
    jmp start_decode

set_rgb_decode:
    mov encodingMode, MODE_RGB24
    jmp start_decode

set_gray_decode:
    mov encodingMode, MODE_GRAYSCALE
    jmp start_decode

decomp_generic:
    mov isBMP, 0
    mov encodingMode, MODE_GENERIC
    mov headerSize, 0

start_decode:
    call RemoveRLEExtension
    mov edx, OFFSET msgDecoding
    call WriteString

    cmp isBMP, 1
    je decode_as_image

    push pOutputBuffer
    push encodedSize
    push pInputBuffer
    call DecodeRLE_Generic
    jmp decode_complete

decode_as_image:
    push pOutputBuffer
    push encodedSize
    push pInputBuffer
    push headerSize
    call DecodeRLE_Image

decode_complete:
    mov decodedSize, eax
    test eax, eax
    jz decode_error

    mov edx, OFFSET msgWriting
    call WriteString
    call WriteDecodedFile
    test eax, eax
    jz write_error_decode

    mov edx, OFFSET msgComplete
    call WriteString
    call Crlf
    mov edx, OFFSET msgDecodedSize
    call WriteString
    mov eax, decodedSize
    call WriteDec
    mov edx, OFFSET msgBytesText
    call WriteString
    mov edx, OFFSET msgSavedDec
    call WriteString
    mov edx, OFFSET decodedFile
    call WriteString
    call Crlf
    jmp cleanup_decode

no_file_decode:
    mov edx, OFFSET msgNoFile
    call WriteString
    jmp decode_done

file_error_decode:
    mov edx, OFFSET msgError
    call WriteString
    mov edx, OFFSET msgFileReadError
    call WriteString
    jmp decode_done

mem_error_decode:
    mov edx, OFFSET msgError
    call WriteString
    mov edx, OFFSET msgMemError
    call WriteString
    jmp decode_done

decode_error:
    mov edx, OFFSET msgError
    call WriteString
    mov edx, OFFSET msgFileReadError
    call WriteString
    jmp cleanup_decode

write_error_decode:
    mov edx, OFFSET msgError
    call WriteString
    mov edx, OFFSET msgFileWriteError
    call WriteString

cleanup_decode:
    cmp pInputBuffer, 0
    je skip_cleanup_input
    INVOKE GlobalFree, pInputBuffer
    mov pInputBuffer, 0
skip_cleanup_input:
    cmp pOutputBuffer, 0
    je skip_cleanup_output
    INVOKE GlobalFree, pOutputBuffer
    mov pOutputBuffer, 0
skip_cleanup_output:

decode_done:
    mov edx, OFFSET msgPressKey
    call WriteString
    call ReadChar
    ret
ProcessDecode ENDP

;============================================================================
; ProcessEncodeAndVerify - Encode and verify data integrity
;============================================================================

ProcessEncodeAndVerify PROC
    call ProcessEncode
    cmp pInputBuffer, 0
    je verify_skip
    cmp pEncodedBuffer, 0
    je verify_skip

    INVOKE GlobalAlloc, GMEM_FIXED, originalSize
    test eax, eax
    jz verify_skip
    mov pOutputBuffer, eax

    mov edx, OFFSET msgDecoding
    call WriteString
    cmp isBMP, 1
    je decode_image_verify

    push pOutputBuffer
    push encodedSize
    push pEncodedBuffer
    call DecodeRLE_Generic
    jmp decoding_done_verify

decode_image_verify:
    push pOutputBuffer
    push encodedSize
    push pEncodedBuffer
    push headerSize
    call DecodeRLE_Image

decoding_done_verify:
    mov decodedSize, eax
    call VerifyData
    call WriteDecodedFile
    INVOKE GlobalFree, pOutputBuffer
    mov pOutputBuffer, 0

verify_skip:
    ret
ProcessEncodeAndVerify ENDP

;============================================================================
; ViewStatistics - Display last encoding statistics
;============================================================================

ViewStatistics PROC
    cmp hasStats, 0
    je no_stats
    call DisplayReport
    jmp stats_done

no_stats:
    mov edx, OFFSET msgNoStats
    call WriteString

stats_done:
    mov edx, OFFSET msgPressKey
    call WriteString
    call ReadChar
    ret
ViewStatistics ENDP

;============================================================================
; Cleanup - Free all allocated memory
;============================================================================

Cleanup PROC
    cmp pInputBuffer, 0
    je skip_cleanup1
    INVOKE GlobalFree, pInputBuffer
skip_cleanup1:
    cmp pEncodedBuffer, 0
    je skip_cleanup2
    INVOKE GlobalFree, pEncodedBuffer
skip_cleanup2:
    cmp pOutputBuffer, 0
    je skip_cleanup3
    INVOKE GlobalFree, pOutputBuffer
skip_cleanup3:
    ret
Cleanup ENDP

;============================================================================
; END OF PROGRAM
;============================================================================

END main
