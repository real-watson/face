
CFLAGS = -Wall
LDFLAGS = -I /usr/local/ffmpeg/include \
	-L /usr/local/ffmpeg/lib \
	-lavdevice \
	-lavformat \
	-lavcodec \
	-lavutil \
	-lavfilter \
	-lswresample \
	-lswscale \
	-larcsoft_face \
	-larcsoft_face_engine 

CPP = -std=c++11
SRC = engine.cpp face.cpp jpeg.cpp util.cpp

all:
	g++ $(CPP) $(SRC) -o test $(LDFLAGS) $(CFLAGS)	
clean:
	rm test
