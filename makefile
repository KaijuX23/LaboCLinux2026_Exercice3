CXX = g++

QT_FLAGS = -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++
QT_LIBS = /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread

MYSQL_FLAGS = -I/usr/include/mysql -m64
MYSQL_LIBS = -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl

all: CLINUX_Exercice3 CreationBD Lecture

CLINUX_Exercice3: main.o mainwindowex3.o moc_mainwindowex3.o
	$(CXX) -o CLINUX_Exercice3 main.o mainwindowex3.o moc_mainwindowex3.o $(QT_LIBS)

main.o: main.cpp
	$(CXX) -c $(QT_FLAGS) -o main.o main.cpp

mainwindowex3.o: mainwindowex3.cpp
	$(CXX) -c $(QT_FLAGS) -o mainwindowex3.o mainwindowex3.cpp

moc_mainwindowex3.o: moc_mainwindowex3.cpp
	$(CXX) -c $(QT_FLAGS) -o moc_mainwindowex3.o moc_mainwindowex3.cpp

CreationBD: CreationBD.cpp
	$(CXX) -o CreationBD CreationBD.cpp $(MYSQL_FLAGS) $(MYSQL_LIBS)

Lecture: Lecture.cpp
	$(CXX) -o Lecture Lecture.cpp $(MYSQL_FLAGS) $(MYSQL_LIBS)

clean:
	rm -f *.o CLINUX_Exercice3 CreationBD Lecture