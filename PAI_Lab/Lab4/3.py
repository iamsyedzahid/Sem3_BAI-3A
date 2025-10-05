class Account:
def init(self):
self.__account_no = None
self.__account_bal = None
self.__security_code = None
def setData(self, no, bal, code):
self.__account_no = no
self.__account_bal = bal
self.__security_code = code
def display(self):
print("Account No: ", self.__account_no)
print("Balance: ", self.__account_bal)
print("Security Code: ", self.__security_code)

a = Account()
a.setData(12345, 5000, 999)
a.display()
