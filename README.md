# testTask

1. Build & run commands
```cpp
mkdir build \
cd build \
cmake ../src \
make -j5

bin/blendJpeg --input ~/Downloads/interlaced.jpg --output out.jpg
```

2. Build and run in Docker
```cpp
docker build -t test_task .

docker run  --mount src=./inout,target=/app/inout,type=bind test_task /app/build/bin/blendJpeg --input /app/inout/interlaced.jpg --output /app/inout/out.jpg
```

3. For each pixel of the output line(except the first one) the average of Y,U,V components is calculated in the following way:
```cpp
f.e. for pixel i:\
blendedRow[i][Y] = 0.5 * (currentRow[i][Y] + previousRow[i][Y]); \
blendedRow[i][U] = 0.5 * (currentRow[i][U] + previousRow[i][U]); \
blendedRow[i][V] = 0.5 * (currentRow[i][V] + previousRow[i][V]); \
```
  
