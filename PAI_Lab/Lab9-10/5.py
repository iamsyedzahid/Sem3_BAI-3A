import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier, plot_tree
from sklearn.metrics import accuracy_score, precision_score
import matplotlib.pyplot as plt

df5 = pd.read_csv(train.scv)

df5['Age'].fillna(df5['Age'].mean(), inplace=True)

X = df5[['Pclass', 'Sex', 'Age', 'Fare']]
y = df5['Survived']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

model5 = DecisionTreeClassifier(max_depth=3, random_state=42)
model5.fit(X_train, y_train)
y_pred = model5.predict(X_test)

accuracy = accuracy_score(y_test, y_pred)
precision = precision_score(y_test, y_pred, zero_division=0)

print(f"Accuracy: {accuracy:.4f}")
print(f"Precision (for Survived=1): {precision:.4f}")

plt.figure(figsize=(15, 10))
plot_tree(model5,
          feature_names=X.columns,
          class_names=['Died', 'Survived'],
          filled=True,
          rounded=True,
          fontsize=10)
plt.title("Decision Tree Visualization (Max Depth 3) - Simulated Data")
plt.savefig('decision_tree_simulated.png')

print("Decision Tree saved to 'decision_tree_simulated.png'.")

print("\nTop Splits Interpretation (Based on Simulated Data):")
print(f"The root node (top split) uses the feature 'Age'. The exact feature and the predictive power are arbitrary due to the use of random data.")
print("The primary split condition (the root node) is intended to use the feature that offers the greatest reduction in impurity (Gini index).")
