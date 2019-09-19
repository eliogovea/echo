echo "building server ..."
cd server
mkdir build
cd build
cmake ..
make

echo "building client ..."
cd ../../
cd client
make

cd ../
mkdir bin
cd bin
cp ../server/build/server .
cp ../client/client .

