FACIL_VER="0.7.5"
FACIL_NAME="facil.io-${FACIL_VER}"
LIBDIR="/usr/local/lib"
INCDIR="/usr/local/include"

wget https://github.com/boazsegev/facil.io/archive/refs/tags/${FACIL_VER}.zip
unzip ${FACIL_VER}.zip
rm -Rf ${FACIL_VER}.zip
cd ${FACIL_NAME} ; mkdir build; cd build; cmake ..; make; mv libfacil.io.a ${LIBDIR} ; cd ..
#mv -f lib/facil ${INCDIR} ; 
cp -rf lib/facil ${INCDIR} ; 
echo `pwd`
cd ..; rm -Rf ${FACIL_NAME}




