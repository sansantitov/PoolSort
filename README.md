# PoolSort
Решение по заданию 30.7.1 (модуль "Многопоточное программирование. Пул потоков")

# Команда
Александр Титов

# Основные черты решения 

Нужно придумать механизм, который переводил бы родительскую задачу в состояние готовности (фьючерс) тогда,
когда все ее подзадачи были совершены.
Задачу можно решить, используя std::promise и std::shared_ptr, где последний поможет в качестве счетчика ссылок на родительскую задачу. 
Продемонстрируйте скорость работы алгоритма быстрой сортировки при использовании пула потоков. 
Учитывайте, что не стоит запускать задачу на вычисление левой части алгоритма в качестве подзадачи, 
если количество элементов в этой части не превосходит 100000 (расходы на захват мьютекса очень велики).


