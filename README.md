# joy_to_twist
# インストール
必要なパッケージは以下
```bash
sudo apt-get install ros-melodic-joy -y
sudo apt-get install ros-melodic-joystick-drivers -y
sudo pip install ds4drv
```

# 有線で接続
PS4コントローラーを有線で接続すると、以下のデバイス名で認識される

```bash
/dev/input/js0
```

実行

```bash
roscore
```

```bash
rosrun joy joy_node
[ INFO] [1631175050.163510303]: Opened joystick: /dev/input/js0. deadzone_: 0.050000.
```

```bash
roslaunch joy_to_twist joy_to_twist.launch
```

```bash
sudo chmod 666 /dev/ttyACM0
rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 
```

# 無線で接続

```bash
sudo pip install ds4drv
```

1.「システム設定」等からPCのBluetooth機能をONにします。

```bash
sudo ds4drv

[info][controller 1] Created devices /dev/input/js0 (joystick) /dev/input/event17 (evdev) 
[info][bluetooth] Scanning for devices
```

2.DS4の「PSボタン」と「SHARE」ボタンを同時に10秒くらい押し続けます。するとコントローラ背後のライトバーがチカチカッ、チカチカッという感じで白く点滅します。こうなったらもうボタンから手を話してOKです。

```bash
[info][bluetooth] Found device DC:0C:2D:CE:0A:07
[info][controller 1] Connected to Bluetooth Controller (DC:0C:2D:CE:0A:07)
[info][bluetooth] Scanning for devices
[info][controller 1] Battery: 87%
```

3.なおペアリング後にds4drvを終了すると、DS4のライトバーが青点灯のまま残ってしまいますが、PSボタンを10秒くらい長押しすると消えます。

4.実行

```bash
sudo ds4drv
```

```bash
source ~/catkin_ws/devel/setup.bash
roslaunch joy_to_twist joy_to_twist.launch
```

```bash
rosrun rosserial_python serial_node.py /dev/ttyACM0 _baud:=115200
```

```bash
linear: 
  x: 0.0
  y: 0.0
  z: 0.0
angular: 
  x: 0.0
  y: 0.0
  z: 0.0
```


# 動作方法
PS4コントローラーで動作確認

- 左スティックを上に傾けると前進
- 左スティックを下に傾けると後退
- 右スティックを右に傾けると右旋回
- 右スティックを左に傾けると左旋回

# 使用目的
- PS4コントローラーでロボットを走行させて、mapを生成
- 自律移動区間以外での人によるロボットの操作時
