# 6.1 下載 MNIST 資料
import numpy as np
import pandas as pd
from keras.units import np_utils
np.random.seed(10)

from keras.datasets import mnist
(X_train_image, y_train_label), (X_test_image, y_test_label) = mnist.load_data()
print('train data=', len(X_train_image))
print('test data=', len(X_test_image)))

# 6.2 查看訓練資料
print('X_train_image: ', X_train_image.shape)
print('y_train_label: ', y_train_label.shape)


from matplotlib import pyplot as plt
def plot_image(image):
    fig = plt.gcf() # 設定圖形大小
    fig.set_size_inches(2, 2)
    plt.imshow(image, cmap='binary') # 以黑白灰階顯示
    plt.show()

plot_image(X_train_image[0])
y_train_label[0]

# 6.3 查看多筆訓練資料 images 與 label
import matplotlib.pyplot as plt
def plot_images_labels_prediction(images, labels, prediction, idx, num=10):
    # images 數字影像, labels 真實的 label, prediction 預測結果
    # idx 從哪個位置開始顯示資料, num 要顯示的資料筆數 
    fig = plt.gcf()
    fig.set_size_inches(12, 14)
    if num > 25: num = 25
    for i in range(0, num):
        ax = plt.subplot(5,5, 1+i)
        ax.imshow(images[idx], cmap='binary')
        title = "label=" + str(labels[idx])
        if len(prediction) > 0:
            title += ", predict=" + str(prediction[idx])

        ax.set_title(title, fontsize=10)
        ax.set_xticks([]) # 設定不顯示刻度
        ax.set_yticks([])
        idx+=1
    plt.show()


# 查看前十筆訓練資料
plot_images_labels_prediction(X_train_image, y_train_label, [], 0, 10)
# 查看測試資料
print('X_test_image: ', X_test_image.shape)
print('y_test_label: ', y_test_label.shape)
# 查看前十筆測試資料
plot_images_labels_prediction(X_test_image, y_test_label, [], 0, 10)


# 6.5 features (訓練資料的特徵值)預處理
# 1. 將 28*28 的影像, reshape 為 1維的向量, 長度變為 784, 並且轉換為 float
x_Train = X_train_image.reshape(60000, 784).astype('float32')
x_Test = X_test_image.reshape(1000, 784).astype('float32')
print('x_Train:', x_Train.shape)
print('x_Test', x_Test.shape)
# 2. 將數字影像 image 的數字標準化
# 數字標準化, 可以提高後續訓練模型的準確率
x_Train_normalize = x_Train / 255
x_Test_normalize = x_Test / 255

# 6.6 labels (真實的值)預處理
# one-hot encoding
# ex: 7 變為 00000001000 剛好對應 輸出層的 10個神經元
y_TrainOneHot = np_utils.to_categorical(y_train_label)
y_TestOneHot = np_utils.to_categorical(y_test_label)



# 7.3 建立模型
# 輸入層(x) 共有 784 個神經元
# 隱藏層(h1) 共有 256 個神經元
# 輸出層(y) 共有 10 個神經元
from keras.models import Sequential
from keras.models import Dense

# 建立線性堆疊模型
model = Sequential()

# 建立並增加 輸入層(x) 及 隱藏層 (h1)
model.add(Dense(units=256, input_dim=784, kernel_initializer='normal', activation='relu'))

# kernel_initializer 使用 normal distribution 常態分佈的亂數, 初始化 weight(權重) 和 bias (偏差)

# 建立輸出層 輸出層(y)
# 不指定 input_dim, 會自己根據上一層的 unit(256), 設定這一層的 input_dim 為 256
model.add(Dense(units=10, kernel_initializer='normal', activation='softmax'))

# 查看模型摘要
print(model.summary())


# 7.4 進行訓練
# 定義模型的訓練方式
model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
# loss: 設定損失參數(loss function), 
# optimizer: 設定訓練時的最佳化方法
# metrics: 設定用何種方式來評估模型

# 開始訓練
train_history = model.fit(x=x_Train_normalize,
                          y=y_TrainOneHot, validation_split=0.2,
                          epochs=10, batch_size=200, verbose=2)
# x: features, y: labels
# validation_split: 設定訓練資料與驗證資料的比例(0.2即表示驗證資料 20%)
# epochs: 執行幾個訓練週期
# batch_size: 每一批次訓練幾筆 
# verbose: 顯示訓練過程

# 資料總共 60000萬筆, 分成訓練資料 48000 + 驗證資料 12000
# 48000筆, 每一批次訓練 200筆, 分成 48000/200 = 240批次訓練

# 以圖像方式顯示 train_history
def show_train_history(train_history, train, validation):
    plt.plot(train_history.history[train])
    plt.plot(train_history.history[validation])
    plt.title('Train History')
    plt.ylabel(train)
    plt.xlabel('Epoch')
    plt.legend(['train', 'validation'], loc='upper left')
    plt.show()
    # train: 訓練資料的執行結果
    # validation: 驗證資料的執行結果


show_train_history(train_history, 'acc', 'val_acc')

# 7.5 以測試資料評估模型準確率
scores = model.evaluate(x_Test_normalize, y_TestOneHot)
print()
print('accuracy=', scores[1])

# 7.6 進行預測
prediction = model.predict_classes(x_Test)
prediction

plot_images_labels_prediction(X_test_image, y_test_label, prediction, idx=340)

