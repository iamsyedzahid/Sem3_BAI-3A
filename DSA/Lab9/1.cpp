/* 
Root is 30
Left Subtree value is 10, Left child: Null, Right child: 20
Right Subtree value is 40, Left child: Null, Right child: 50

Compare 15 with the root (30): 15 < 30, so move to the left child (10).
Compare 15 with 10: 15 > 10, so move to the right child (20).
Compare 15 with 20: 15 < 20, so move to the left child of 20.
15 is inserted as the left child of 20.

Tree after Insertion (Before Rebalancing):
Root: 30
Root->Left Child: 10
    Root->Left->Right Child: 20
        Root->Left->Right->Left Child: 15 (New Node)
Root->Right Child: 40
Root->Right->Right Child: 50

Node 15: BF = 0 - 0 = 0
Node 20: Height of Left Subtree (15) is 1.
Height of Right Subtree (None) is 0.
BF = 1 - 0 = 1
Node 10: Height of Left Subtree (None) is 0.
Height of Right Subtree (20, 15) is 2.
BF = 0 - 2 = -2 (Imbalance)

A single left rotation will be a Right-Right (RR) imbalance.

Left Rotation on Node 10:
Let Z be 10 and Y be 20.
The left subtree of Y is 15 (Let this be T2).
Y (20) becomes the new parent of Z (10).
T2 (15) becomes the new right child of Z (10).
Node 10's New Right Child: 15
Node 20's New Left Child: 10

Root: 30

    Root->Left Child: 20

      Root->Left->Left Child: 10

        Root->Left->Left->Right Child: 15
      Root->Left->Right Child: None
    Root->Right Child: 40
      Root->Right->Right Child: 50

The height of the resulting AVL tree is 3.
  
*/
