echo $0

DEMO_ROOT=`pwd`/`dirname $0`
echo "DEMO_ROOT $DEMO_ROOT"

# Fetch NextCAS-SDK, SDK Plugin
git clone git@118.31.50.10:tudou/NextCAS-SDK.git ${DEMO_ROOT}/Plugins/NextCAS-SDK -b sdk

# Fetch NHMiniZip, Zip Plugin
# git clone git@118.31.50.10:tudou/NHMiniZip.git ${DEMO_ROOT}/Plugins/NHMiniZip -b main

# Fetch NHMMKV, Key-Value cache Plugin
# git clone git@118.31.50.10:tudou/NHMMKV.git ${DEMO_ROOT}/Plugins/NHMMKV -b main

# Fetch NextCAS-Assets
# git clone git@118.31.50.10:tudou/NextCAS-Assets.git ${DEMO_ROOT}/Plugins/NextCAS-Assets -b main

# Copy Unreal Assets
# mkdir /p ${DEMO_ROOT}/Plugins/NextCAS-Assets/Paks/
# cp -r //WeMetaNAS/wemeta-application/NextCAS-SDK/Paks/ ${DEMO_ROOT}/Plugins/NextCAS-Assets/Paks/
