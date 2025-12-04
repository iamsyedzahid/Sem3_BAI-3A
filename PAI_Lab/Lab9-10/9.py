import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split

try:
    df9 = pd.read_csv('laptop_prices.csv')
    print("Successfully loaded 'laptop_prices.csv'.")
except FileNotFoundError:
    print("Error: 'laptop_prices.csv' not found. Cannot proceed.")
    exit()

target = 'Price_euros'

df9['Ram'] = df9['Ram'].astype(str).str.replace(r'GB', '', regex=True).astype(int)

df9['Weight'] = df9['Weight'].astype(str).str.replace(r'kg', '', regex=True).astype(float)

df9['PrimaryStorage'] = df9['PrimaryStorage'].astype(str).str.replace(r'GB', '', regex=True).str.replace(r'TB', '000', regex=True).astype(int)
df9['SecondaryStorage'] = df9['SecondaryStorage'].astype(str).str.replace(r'GB', '', regex=True).str.replace(r'TB', '000', regex=True).astype(int)
df9['StorageSize'] = df9['PrimaryStorage'] + df9['SecondaryStorage']

features = ['Ram', 'Weight', 'CPU_freq', 'StorageSize']
X = df9[features]
y = df9[target]

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

model_unscaled = LinearRegression()
model_unscaled.fit(X_train, y_train)
y_pred_unscaled = model_unscaled.predict(X_test)

r2_unscaled = r2_score(y_test, y_pred_unscaled)
rmse_unscaled = np.sqrt(mean_squared_error(y_test, y_pred_unscaled))

scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

model_scaled = LinearRegression()
model_scaled.fit(X_train_scaled, y_train)
y_pred_scaled = model_scaled.predict(X_test_scaled)

r2_scaled = r2_score(y_test, y_pred_scaled)
rmse_scaled = np.sqrt(mean_squared_error(y_test, y_pred_scaled))

print("\n Model Performance Comparison ")
print(f"Unscaled Model R²: {r2_unscaled:.4f}")
print(f"Scaled Model R²:   {r2_scaled:.4f}")
print("-" * 30)
print(f"Unscaled Model RMSE: €{rmse_unscaled:,.2f}")
print(f"Scaled Model RMSE:   €{rmse_scaled:,.2f}")

print("\nDiscussion on Scaling:")
print("For standard Linear Regression, feature scaling (StandardScaler) does not change the R² or RMSE performance because linear models are invariant to the scaling of predictors (it only changes the magnitude of the coefficients and the intercept). Both models should produce identical metrics.")

scaled_coefficients = pd.Series(model_scaled.coef_, index=features).abs().sort_values(ascending=False)

print("\n Feature Impact (Standardized Coefficients) ")
print(scaled_coefficients)
print(f"\nThe most significant predictor of laptop price (based on standardized coefficients) is **{scaled_coefficients.index[0]}**.")
