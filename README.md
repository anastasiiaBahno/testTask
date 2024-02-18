# testTask

1. Build & run commands

mkdir build \
cd build \
cmake ../src \
make -j5 

bin/blendJpeg --input ~/Downloads/interlaced.jpg --output out.jpg

2. Build and run in Docker
	
	docker build -t test_task .

	docker run  --mount src=./inout,target=/app/inout,type=bind test_task /app/build/bin/blendJpeg --input /app/inout/interlaced.jpg --output /app/inout/out.jpg

3. 
   1. “Blending” algorithm: line N in the output image is the average of lines N and N-1 from the input image.\
       Does it mean that for every pixel average for every channel is calculated separatly?

       f.e. for pixel i:\
       blendedRow[i][Y] = 0.5 * (currentRow[i][Y] + previousRow[i][Y]); \
       blendedRow[i][U] = 0.5 * (currentRow[i][U] + previousRow[i][U]); \
       blendedRow[i][V] = 0.5 * (currentRow[i][V] + previousRow[i][V]); \
   2. Is optimization  expected?
