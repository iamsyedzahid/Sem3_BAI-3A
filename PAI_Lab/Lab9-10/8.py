import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split

try:
    df8 = pd.read_csv('train.csv')
    print("Successfully loaded 'train.csv'.")
except FileNotFoundError:
    print("Error: 'train.csv' not found. Cannot proceed with actual data.")
    exit()

features = ['OverallQual', 'GrLivArea', 'GarageCars', 'YearBuilt']
target = 'SalePrice'

df8.dropna(subset=[target], inplace=True)

X = df8[features]
y = df8[target]

print("\nChecking for and imputing missing values:")
for feature in features:
    if X[feature].isnull().any():
        mean_val = X[feature].mean()
        X[feature].fillna(mean_val, inplace=True)
        print(f"Imputed missing values in {feature} with mean: {mean_val:.2f}")

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

model8 = LinearRegression()
model8.fit(X_train, y_train)
y_pred = model8.predict(X_test)

print("\nModel Coefficients (Unscaled):")
for feature, coef in zip(features, model8.coef_):
    print(f"{feature}: {coef:.2f}")

print(f"Intercept: {model8.intercept_:.2f}")
print("Interpretation: A positive coefficient (e.g., GrLivArea) means that a one-unit increase in that feature is associated with an increase in SalePrice, holding others constant.")

r_squared8 = r2_score(y_test, y_pred)
rmse8 = np.sqrt(mean_squared_error(y_test, y_pred))

print(f"\nR² Value (Test Set): {r_squared8:.4f}")
print(f"RMSE (Root Mean Squared Error, Test Set): ${rmse8:,.2f}")

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)
model8_scaled = LinearRegression()
model8_scaled.fit(X_scaled, y)

scaled_coefficients = pd.Series(model8_scaled.coef_, index=features).abs().sort_values(ascending=False)

print("\nFeature Impact (Standardized Coefficients):")
print(scaled_coefficients)
print(f"The feature with the largest absolute standardized coefficient is **{scaled_coefficients.index[0]}**, indicating it impacts price the most.")
