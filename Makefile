
all: build

gtrl/bin: gtrl/*.ino
	arduino --verify --pref build.path=$@ gtrl/gtrl.ino

build: gtrl/bin

upload: gtrl/bin
	arduino --upload --pref build.path=gtrl/bin gtrl/gtrl.ino

clean:
	rm -rf gtrl/bin
