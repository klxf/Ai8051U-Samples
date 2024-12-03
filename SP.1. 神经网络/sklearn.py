import json
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import classification_report, confusion_matrix

# 读取 JSON 文件
with open('data.json', 'r') as file:
    data = json.load(file)

# 提取特征和标签
X = np.array([item['data'] for item in data])
y = np.array([item['label'] for item in data])

# 将数据集分为训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=1089890203)

# 定义神经网络模型
mlp = MLPClassifier(hidden_layer_sizes=(8, 8), max_iter=500, random_state=1089890203, learning_rate_init=0.005)

# 训练模型
mlp.fit(X_train, y_train)

# 在测试集上进行预测
y_pred = mlp.predict(X_test)

# 输出分类报告
print(classification_report(y_test, y_pred, zero_division=1))

# 输出混淆矩阵
cm = confusion_matrix(y_test, y_pred)
print("混淆矩阵:")
print(cm)

# 输出训练的准确率
accuracy = mlp.score(X_test, y_test)
print("准确率: {:.2f}%".format(accuracy * 100))

# 输出各个神经元的参数和标签的映射关系
nn_parameters = {}
for i, layer_weights in enumerate(mlp.coefs_):
    nn_parameters[f"Layer {i} weights"] = layer_weights.tolist()

# 将神经网络的参数和标签的映射关系输出到文件
with open('neural_network_parameters.json', 'w') as f:
    json.dump(nn_parameters, f, indent=4)
