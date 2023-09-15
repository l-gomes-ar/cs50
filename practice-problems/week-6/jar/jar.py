class Jar:
    def __init__(self, capacity=12):
        self._capacity = capacity
        self._size = 0

        if capacity < 0:
            raise ValueError("Jar cannot hold negative cookies!")

    def __str__(self):
        return "🍪" * self._size

    def deposit(self, n):
        self._size += n

        if self._size > self._capacity:
            raise ValueError("Not enough space in Jar!")

    def withdraw(self, n):
        self._size -= n

        if self._size < 0:
            raise ValueError("Not enough cookies to remove!")

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

def main():
    jar = Jar()
    jar.deposit(12)
    jar.withdraw(6)
    print(str(jar))


main()