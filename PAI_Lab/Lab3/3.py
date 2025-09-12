def employee(name, salary=None):
    if salary is None:
        salary_taxed = 10000
        print(f"The salary of the {name} is {salary_taxed}.")
    else:
        salary_taxed = salary* 0.98
        print(f"The salary of the {name} is {salary_taxed}.")

employee("zahid")