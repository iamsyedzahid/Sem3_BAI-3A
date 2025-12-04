import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.preprocessing import StandardScaler

df = pd.read_csv('kl.csv', encoding='utf-8')

features = ['Overall', 'Potential', 'Age', 'International Reputation']
target = 'Value'

df_clean = df[features + [target]].dropna()

def convert_value(val):
    if isinstance(val, str):
        val = val.replace('Ć', '').replace(',', '')
        if 'M' in val:
            return float(val.replace('M', '')) * 1e6
        elif 'K' in val:
            return float(val.replace('K', '')) * 1e3
    return float(val)

df_clean[target] = df_clean[target].apply(convert_value)

X = df_clean[features]
y = df_clean[target]

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)
y_pred = model.predict(X_test)

mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

coeff_df = pd.DataFrame({
    'Feature': features,
    'Coefficient': model.coef_
}).sort_values(by='Coefficient', key=abs, ascending=False)

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)
X_train_s, X_test_s, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)

model_scaled = LinearRegression()
model_scaled.fit(X_train_s, y_train)

coeff_scaled = pd.DataFrame({
    'Feature': features,
    'Scaled Coefficient': model_scaled.coef_
}).sort_values(by='Scaled Coefficient', key=abs, ascending=False)

features_no_pot = ['Overall', 'Age', 'International Reputation']
X_no_pot = df_clean[features_no_pot]

X_train_no, X_test_no, y_train, y_test = train_test_split(X_no_pot, y, test_size=0.2, random_state=42)

model_no_pot = LinearRegression()
model_no_pot.fit(X_train_no, y_train)
y_pred_no = model_no_pot.predict(X_test_no)

mse_no = mean_squared_error(y_test, y_pred_no)
r2_no = r2_score(y_test, y_pred_no)

print("Model with Potential - MSE:", mse, "R²:", r2)
print("Model without Potential - MSE:", mse_no, "R²:", r2_no)
print("\nFeature impact ranking:")
print(coeff_scaled)
