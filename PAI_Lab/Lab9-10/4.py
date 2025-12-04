data4_original = {
    'Height (cm)': [150, 155, 160, 165, 170, 175, 180],
    'Weight (kg)': [50, 55, 60, 63, 68, 72, 75]
}
df4_original = pd.DataFrame(data4_original)

import pandas as pd
from sklearn.linear_model import LinearRegression

X_original = df4_original[['Height (cm)']]
y_original = df4_original['Weight (kg)']
model3 = LinearRegression()
model3.fit(X_original, y_original)

r2_original = model3.score(df4_original[['Height (cm)']], df4_original['Weight (kg)'])

outlier = {'Height (cm)': [190], 'Weight (kg)': [60]}
df4_with_outlier = pd.concat([df4_original, pd.DataFrame(outlier)], ignore_index=True)

X_outlier = df4_with_outlier[['Height (cm)']]
y_outlier = df4_with_outlier['Weight (kg)']

model4_outlier = LinearRegression()
model4_outlier.fit(X_outlier, y_outlier)

r2_outlier = model4_outlier.score(X_outlier, y_outlier)

comparison = pd.DataFrame({
    'Metric': ['Intercept (kg)', 'Slope (kg/cm)', 'R² Value'],
    'Without Outlier': [model3.intercept_, model3.coef_[0], r2_original],
    'With Outlier': [model4_outlier.intercept_, model4_outlier.coef_[0], r2_outlier]
})

print(comparison.set_index('Metric').round(4))

print(f"\n Discussion:\nThe outlier (190 cm, 60 kg) has a large Height value (high leverage) but a relatively low Weight for that height, causing it to exert a strong pull on the regression line towards itself.")
print(f"Effect: The Slope** decreased (from {model3.coef_[0]:.4f} to {model4_outlier.coef_[0]:.4f}), meaning the predicted increase in Weight per cm of Height is smaller in the new model.")
