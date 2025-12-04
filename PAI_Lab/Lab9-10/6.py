import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score

df_processed = pd.read_csv('train.csv')

df_processed.loc[df_processed.sample(frac=0.2).index, 'Age'] = np.nan

df_processed['Age'].fillna(df_processed['Age'].mean(), inplace=True)

df_processed['Fare'].fillna(df_processed['Fare'].mean(), inplace=True)

embarked_mode = df_processed['Embarked'].mode()[0]
df_processed['Embarked'].fillna(embarked_mode, inplace=True)

df_processed['Sex'] = df_processed['Sex'].map({'male': 0, 'female': 1})

df_processed = pd.get_dummies(df_processed, columns=['Embarked'], prefix='Embarked', drop_first=True)

features = ['Pclass', 'Sex', 'Age', 'Fare', 'Embarked_Q', 'Embarked_S']
X = df_processed[features]
y = df_processed['Survived']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

model_dt = DecisionTreeClassifier(max_depth=3, random_state=42)
model_dt.fit(X_train, y_train)
y_pred = model_dt.predict(X_test)

accuracy = accuracy_score(y_test, y_pred)

print("\n--- Preprocessing Steps ---")
print(f"Age imputed with Mean: {df_processed['Age'].mean():.2f}")
print(f"Embarked imputed with Mode: {embarked_mode}")
print("Sex converted to numeric (0/1).")
print("Embarked converted to One-Hot Encoded features (Embarked_Q, Embarked_S).")

print("\n--- Model Performance ---")
print(f"Final Model Accuracy (on simulated data): {accuracy:.4f}")
print("\nDiscussion: Preprocessing was essential to transform categorical and missing data into a numeric format compatible with the Decision Tree model, enabling the classification task to proceed.")
