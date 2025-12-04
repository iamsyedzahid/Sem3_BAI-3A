import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression

data1 = {
    'YearsExperience': [1.1, 1.3, 1.5, 2.0, 2.2, 2.9, 3.0, 3.2, 3.2, 3.7],
    'Salary': [39.0, 46.0, 47.0, 52.0, 56.0, 64.0, 65.0, 67.0, 68.0, 70.0]
}
df1 = pd.DataFrame(data1)

X = df1[['YearsExperience']]
y = df1['Salary']

model1 = LinearRegression()
model1.fit(X, y)

intercept = model1.intercept_
slope = model1.coef_[0]

print("--- Q1 Results ---")
print(f"Estimated Intercept (β₀): {intercept:.2f} thousand")
print(f"Estimated Slope (β₁): {slope:.2f} thousand/year")

years_of_experience = 4.5
prediction = model1.predict(np.array([[years_of_experience]]))
print(f"Predicted Salary for {years_of_experience} years: {prediction[0]:.2f} thousand")

r_squared = model1.score(X, y)
print(f"R² Value: {r_squared:.4f}")
