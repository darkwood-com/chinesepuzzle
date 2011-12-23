# set params
ANDROID_NDK_ROOT=/Applications/Programmation/android-ndk-r7
COCOS2DX_ROOT=/Users/math/Mathieu/Programmation/Programmation/ChinesePuzzle/ChinesePuzzle/Common/Src/Externals/Cocos2Dx
GAME_ROOT=/Users/math/Mathieu/Programmation/Programmation/ChinesePuzzle/ChinesePuzzle/Android
GAME_ANDROID_ROOT=$GAME_ROOT/Project
RESOURCE_ROOT=$GAME_ROOT/Bin

# make sure assets is exist
if [ -d $GAME_ANDROID_ROOT/assets ]; then
    rm -rf $GAME_ANDROID_ROOT/assets
fi

mkdir $GAME_ANDROID_ROOT/assets

# copy resources
for file in $RESOURCE_ROOT/*
do
    if [ -d $file ]; then
        cp -rf $file $GAME_ANDROID_ROOT/assets
    fi

    if [ -f $file ]; then
        cp $file $GAME_ANDROID_ROOT/assets
    fi
done

# build
$ANDROID_NDK_ROOT/ndk-build -C $GAME_ANDROID_ROOT $*

