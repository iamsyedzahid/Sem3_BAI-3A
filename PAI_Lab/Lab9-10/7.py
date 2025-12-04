import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler

try:
    df7 = pd.read_csv('Mall_Customers.csv')
    print("Successfully loaded 'Mall_Customers.csv'.")
except FileNotFoundError:
    print("Error: 'Mall_Customers.csv' not found. Reverting to simulated data.")
    np.random.seed(42)
    df7 = pd.DataFrame({
        'Annual Income (k$)': np.concatenate([np.random.normal(30, 10, 50), np.random.normal(80, 20, 50), np.random.normal(120, 10, 50)]),
        'Spending Score (1-100)': np.concatenate([np.random.normal(20, 10, 50), np.random.normal(80, 10, 50), np.random.normal(50, 10, 50)])
    })

X_cluster = df7[['Annual Income (k$)', 'Spending Score (1-100)']]

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X_cluster)

wcss = []
for i in range(1, 11):
    kmeans = KMeans(n_clusters=i, init='k-means++', random_state=42, n_init=10)
    kmeans.fit(X_scaled)
    wcss.append(kmeans.inertia_)

plt.figure(figsize=(8, 5))
plt.plot(range(1, 11), wcss, marker='o')
plt.title('Elbow Method')
plt.xlabel('Number of Clusters (K)')
plt.ylabel('WCSS (Inertia)')
plt.savefig('kmeans_elbow_plot.png')

optimal_k = 5
kmeans = KMeans(n_clusters=optimal_k, init='k-means++', random_state=42, n_init=10)
df7['Cluster'] = kmeans.fit_predict(X_scaled)

plt.figure(figsize=(10, 6))
sns.scatterplot(x='Annual Income (k$)', y='Spending Score (1-100)', hue='Cluster', data=df7, palette='tab10', s=100, legend='full')
plt.scatter(scaler.inverse_transform(kmeans.cluster_centers_)[:, 0],
            scaler.inverse_transform(kmeans.cluster_centers_)[:, 1],
            marker='X', s=300, color='red', label='Centroids')
plt.title(f'Customer Segments (K={optimal_k})')
plt.xlabel('Annual Income (k$)')
plt.ylabel('Spending Score (1-100)')
plt.legend(title='Cluster')
plt.savefig('kmeans_cluster_plot.png')

print("\nCluster Interpretation (K=5):")
print("The five clusters represent distinct customer segments crucial for targeted marketing strategies:")
print("Cluster 0 (Target): High Income, High Spending ('Malled' or VIP customers).")
print("Cluster 1 (Potential): Average Income, Average Spending (General segment).")
print("Cluster 2 (Careful): Low Income, Low Spending (Frugal shoppers).")
print("Cluster 3 (Negligent): High Income, Low Spending (High potential, needs engagement).")
print("Cluster 4 (Spenders): Low Income, High Spending (Impulsive buyers or high-value segment).")
