
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

all:
	g++ -std=c++11 engine.cpp face.cpp jpeg.cpp -o test $(LDFLAGS) $(CFLAGS)	
clean:
	rm test
