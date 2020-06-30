# -*- coding: UTF-8 -*-

import csv
import numpy as np
from numpy import matrix
from math import pow
from collections import namedtuple
import math
import random
import os
import json

class OCRNeuralNetwork:
    LEARNING_RATE = 0.1
    WIDTH_IN_PIXELS = 20
    # 保存神经网络的文件路径
    NN_FILE_PATH = 'nn.json'

    def __init__(self, num_hidden_nodes, data_matrix, data_labels, training_indices, use_file=True):
        # sigmoid函数
        # 使用numpy的vectorize能得到标量函数的向量化版本
        self.sigmoid = np.vectorize(self._sigmoid_scalar)
        # sigmoid求导函数
        self.sigmoid_prime = np.vectorize(self._sigmoid_prime_scalar)
        # 决定了要不要导入nn.json
        self._use_file = use_file
        # 数据集
        self.data_matrix = data_matrix
        self.data_labels = data_labels
        # 有几层神经网络
        self.num_layers = 0

        if (not os.path.isfile(OCRNeuralNetwork.NN_FILE_PATH) or not use_file):
            # 初始化神经网络
            self.weights1 = self._rand_initialize_weights(400, num_hidden_nodes)
            self.weights2 = self._rand_initialize_weights(num_hidden_nodes, 10)
            self.input_layer_bias = self._rand_initialize_weights(1, num_hidden_nodes)
            self.hidden_layer_bias = self._rand_initialize_weights(1, 10)

            # 训练并保存
            TrainData = namedtuple('TrainData', ['y0', 'label'])
            epochs = 10
            for i in range(epochs):
                self.train([TrainData(self.data_matrix[i], int(self.data_labels[i])) for i in training_indices])
            self.save()
        else:
            # 如果nn.json存在则加载
            self._load()

    def _rand_initialize_weights(self, size_in, size_out):
        return [((x * 0.12) - 0.06) for x in np.random.rand(size_out, size_in)]

    def _sigmoid_scalar(self, z):
        return 1.0 / (1.0 + np.exp(-z))
        # return 1 / (1 + math.e ** -z)

    def _sigmoid_prime_scalar(self, z):
        """Derivative of the sigmoid function."""
        return self._sigmoid_scalar(z) * (1 - self._sigmoid_scalar(z))
        # return z * (1 - z)


    def train(self, training_data_array):
        for data in training_data_array:
            # 前向传播得到结果向量
			# y1=sigmoid(W1*y0+b)
            y1 = np.dot(np.mat(self.weights1), np.mat(data.y0).T)
            sum1 = y1 + np.mat(self.input_layer_bias)
            y1 = self.sigmoid(sum1)

            # y2=sigmoid(W2*y1+b)
			
			

            # 后向传播			
            actual_vals = [0] * 10
            actual_vals[data.label] = 1
			# 计算输出层的误差向量
			# output_errors=actual_vals.T-y2
			
			
			
			# 计算中间层的误差向量
			# hidden_errors=W2*output_errors*sigmoid_prime(sum1)
			
			

            # 更新权重矩阵与偏置向量
			# weights += LEARNING_RATE * errors * y
			# bias += LEARNING_RATE * errors
			
            

    def predict(self, test):
        y1 = np.dot(np.mat(self.weights1), np.mat(test).T)
        y1 =  y1 + np.mat(self.input_layer_bias) # Add the bias
        y1 = self.sigmoid(y1)

        y2 = np.dot(np.array(self.weights2), y1)
        y2 = np.add(y2, self.hidden_layer_bias) # Add the bias
        y2 = self.sigmoid(y2)

        results = y2.T.tolist()[0]
        return results.index(max(results))

    def save(self):
        if not self._use_file:
            return

        json_neural_network = {
            "weights1":[np_mat.tolist()[0] for np_mat in self.weights1],
            "weights2":[np_mat.tolist()[0] for np_mat in self.weights2],
            "b1":self.input_layer_bias[0].tolist()[0],
            "b2":self.hidden_layer_bias[0].tolist()[0]
        }
        with open(OCRNeuralNetwork.NN_FILE_PATH,'w') as nnFile:
            json.dump(json_neural_network, nnFile)

    def _load(self):
        if not self._use_file:
            return

        with open(OCRNeuralNetwork.NN_FILE_PATH) as nnFile:
            nn = json.load(nnFile)
        self.weights1 = [np.array(li) for li in nn['weights1']]
        self.weights2 = [np.array(li) for li in nn['weights2']]
        self.input_layer_bias = [np.array(nn['b1'][0])]
        self.hidden_layer_bias = [np.array(nn['b2'][0])]

