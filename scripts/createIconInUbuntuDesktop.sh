Desktop=`xdg-user-dir DESKTOP`
echo "[Desktop Entry]" > ${Desktop}/VertSys.desktop
echo "Version=1.0" >> ${Desktop}/VertSys.desktop
echo "Name=VertSys" >> ${Desktop}/VertSys.desktop
echo "Exec="$1 >> ${Desktop}/VertSys.desktop
echo "Icon="$2 >> ${Desktop}/VertSys.desktop
echo "Terminal=false" >> ${Desktop}/VertSys.desktop
echo "Type=Application" >> ${Desktop}/VertSys.desktop
echo "Categories=Utility;Application;" >> ${Desktop}/VertSys.desktop
chmod +x ${Desktop}/VertSys.desktop
