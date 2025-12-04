import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression
from scipy.stats import pearsonr
import matplotlib.pyplot as plt
import seaborn as sns

np.random.seed(42)
N = 100
screen_time = np.random.uniform(2.5, 8.0, N)
battery_drain = 1000 + screen_time * 400 + np.random.normal(0, 250, N)

df_simulated = pd.DataFrame({
    'Screen On Time (hours/day)': screen_time,
    'Battery Drain (mAh/day)': battery_drain
})

X = df_simulated[['Screen On Time (hours/day)']]
Y = df_simulated['Battery Drain (mAh/day)']

model = LinearRegression()
model.fit(X, Y)

slope = model.coef_[0]
intercept = model.intercept_
r_squared = model.score(X, Y)

corr, p_value = pearsonr(df_simulated['Screen On Time (hours/day)'], df_simulated['Battery Drain (mAh/day)'])

print("  Results: Screen On Time vs. Battery Drain ")
print(f"Regression Equation: Battery Drain (mAh/day) = {intercept:.2f} + {slope:.2f} * Screen On Time (hours/day)")
print(f"R² Value: {r_squared:.4f}")
print(f"Pearson Correlation Coefficient (r): {corr:.4f}")
print(f"P-value for correlation: {p_value:.4f}")
print("-" * 50)

print("Correlation Investigation:")
print("Note: The original task expected a negative correlation with Battery *Life*. Using Battery *Drain* results in a positive correlation, which is functionally equivalent (high drain means low life).")
if p_value < 0.05:
    print(f"The relationship is statistically significant (p < 0.05).")
    if corr > 0:
        print(f"The correlation (r = {corr:.4f}) is positive and significant. This means as Screen On Time increases, Battery Drain significantly increases.")
    else:
        print(f"The correlation (r = {corr:.4f}) is negative and significant. This means as Screen On Time increases, Battery Drain significantly decreases (unexpected based on real-world physics).")
else:
    print(f"The relationship is not statistically significant (p > 0.05).")

plt.figure(figsize=(8, 6))
sns.scatterplot(x='Screen On Time (hours/day)', y='Battery Drain (mAh/day)', data=df_simulated)
plt.plot(X, model.predict(X), color='red', label=f'Regression Line (r={corr:.2f})')
plt.title('Screen On Time vs. Battery Drain')
plt.xlabel('Screen On Time (hours/day)')
plt.ylabel('Battery Drain (mAh/day)')
plt.legend()
plt.show()
