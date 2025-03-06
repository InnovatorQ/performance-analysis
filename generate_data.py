import random
def generate_special_data(filename, num, data_type="random"):
    with open(filename, 'w') as f:
        if data_type == "random":
            data = [random.randint(-500000, 500000) for _ in range(num)]
        elif data_type == "sorted":
            data = sorted(random.randint(-500000, 500000) for _ in range(num))
        elif data_type == "reverse_sorted":
            data = sorted((random.randint(-500000, 500000) for _ in range(num)), reverse=True)
        elif data_type == "partial_sorted":
            data = sorted(random.randint(-500000, 500000) for _ in range(num//2))
            data += [random.randint(-500000, 500000) for _ in range(num - num//2)]
        elif data_type == "repeated":
            data = [random.choice([-1, 0, 1]) for _ in range(num)]
        
        for num in data:
            f.write(f"{num}\n")

# 生成不同特征的测试数据
generate_special_data("data1.txt", 50000, "random")
generate_special_data("data2.txt", 60000, "sorted")
generate_special_data("data3.txt", 70000, "reverse_sorted")
generate_special_data("data4.txt", 80000, "partial_sorted")
generate_special_data("data5.txt", 90000, "repeated")