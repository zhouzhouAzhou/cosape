# http://t.zoukankan.com/weichao975-p-8276448.html
# �޸����е�Makefile��ʹ���·��ΪcodeblocksĬ��·���������һֱ��ʾ��û��build

# �����¼�Ŀ¼���룬make�ļ�Ĭ��Ӧ��ʹ�� cd c0misc; $(MAKE) ��д��ʽ��
# ��cmd�ָ����� &�������ǡ�;�� Ӧ��ʹ�ã�cd c0misc & $(MAKE);
# Ϊ�˿���ֲ�ԣ�ʹ��make -C������-C��ʾ����Ŀ¼��

test_one:default
	gcc main.c -o bin\Debug\coasep
	$(MAKE) -C c5disk

default:
	gcc main.c -o bin\Debug\coasep

all: main.c
	gcc main.c -o bin\Debug\coasep
	gcc main.c -o coasep
	$(MAKE) -C c0misc
	$(MAKE) -C c2data
	$(MAKE) -C c3CPU
	$(MAKE) -C c4memory_cache
	$(MAKE) -C c6parallel
	$(MAKE) -C c7performance_optimization

#cmd��û��rm,ʹ��del�滻
clean:
	del -f *.exe
	$(MAKE) -C c0misc clean


