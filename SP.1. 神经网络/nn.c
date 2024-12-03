#include <nn.h>

// 激活函数
float relu(float x) {
    return (x > 0) ? x : 0;
}

// 向前传播
void forward(unsigned char input[][64], float output[][10])
{
	float layer0Output[][8] = {{0}};
	float layer1Output[][8] = {{0}};
	float sum;
	unsigned char i, j, k;
	
	for(i = 0; i < 1; i++)
	{
		for(j = 0; j < 8; j++)
		{
			sum = 0;
			for(k = 0; k < 64; k++)
			{
				sum += input[i][k] * Layer0[k][j];
			}
			layer0Output[i][j] = relu(sum);
		}
	}
	
	for(i = 0; i < 1; i++)
	{
		for(j = 0; j < 8; j++)
		{
			sum = 0;
			for(k = 0; k < 8; k++)
			{
				sum += layer0Output[i][k] * Layer1[k][j];
			}
			layer1Output[i][j] = relu(sum);
		}
	}
	
	for(i = 0; i < 1; i++)
	{
		for(j = 0; j < 10; j++)
		{
			sum = 0;
			for(k = 0; k < 8; k++)
			{
				sum += layer1Output[i][k] * Layer2[k][j];
			}
			output[i][j] = relu(sum);
		}
	}
}

// 提取结果
unsigned char findResult(float arr[][10]) {
	unsigned char i;
	float max = arr[0][0];
	unsigned char maxIndex = 0;

	for (i = 1; i < 10; i++) {
		if (arr[0][i] > max) {
			max = arr[0][i];
			maxIndex = i;
		}
	}

	return maxIndex;
}