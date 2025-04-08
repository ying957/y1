main:main.o xyd_deal_data.o xyd_helmet_msg.o mysockapi.o
	gcc $^ -o $@ -lpthread 
%.o:%.c
	gcc -c $<  -o $@ -lpthread -lmysqlclient

clean:
	rm ./*o  main_new
