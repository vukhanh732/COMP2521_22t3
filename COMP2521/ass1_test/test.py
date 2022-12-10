a_list = [10, 5, 12, 11]
a = 6
b = 13


def q1a_func(a_list, a, b):
    for i in range(len(a_list)):
        if (a_list[i] >= a  and a_list[i] < b):
            t = True
        else:
            return False
    return t

print(check(a_list, a, b))