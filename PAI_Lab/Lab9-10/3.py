import matplotlib.pyplot as plt
import seaborn as sns

data3 = {
    'Height (cm)': [150, 155, 160, 165, 170, 175, 180],
    'Weight (kg)': [50, 55, 60, 63, 68, 72, 75]
}
df3 = pd.DataFrame(data3)

X = df3[['Height (cm)']]
y = df3['Weight (kg)']

model3 = LinearRegression()
model3.fit(X, y)

height_to_predict = 172
predicted_weight = model3.predict(np.array([[height_to_predict]]))[0]
print(f"Predicted Weight for 172 cm: {predicted_weight:.2f} kg")

plt.figure(figsize=(8, 5))
sns.scatterplot(x='Height (cm)', y='Weight (kg)', data=df3, label='Data Points')
plt.plot(X, model3.predict(X), color='red', label='Regression Line')
plt.title('Weight vs. Height with Regression Line')
plt.xlabel('Height (cm)')
plt.ylabel('Weight (kg)')
plt.legend()
plt.grid(True)
plt.show()

df3['Predicted Weight'] = model3.predict(X)
df3['Residuals'] = df3['Weight (kg)'] - df3['Predicted Weight']

plt.figure(figsize=(8, 5))
sns.scatterplot(x=df3['Predicted Weight'], y=df3['Residuals'])
plt.axhline(y=0, color='red', linestyle='--')
plt.title('Residuals Plot')
plt.xlabel('Predicted Weight (kg)')
plt.ylabel('Residuals (Actual - Predicted)')
plt.grid(True)
plt.show()
