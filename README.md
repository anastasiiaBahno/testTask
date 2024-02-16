# testTask

1. Build commands

mkdir build \
cd build \
cmake ../src \
make -j5 

2. Run commands

bin/blendJpeg --input ~/Downloads/interlaced.jpg --output out.jpg

3. todo\
   “Blending” algorithm: line N in the output image is the average of lines N and N-1 from the
input image.\

Does it mean that for every pixel average for every channel is calculated separatly?

f.e. for pixel i:\
blendedRow[i][Y] = 0.5 * (currentRow[i][Y] + previousRow[i][Y]); \
blendedRow[i][U] = 0.5 * (currentRow[i][U] + previousRow[i][U]); \
blendedRow[i][V] = 0.5 * (currentRow[i][V] + previousRow[i][V]); \
