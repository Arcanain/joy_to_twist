# joy_to_twist
実行方法は以下の通り

```bash
source ~/catkin_ws/devel/setup.bash
roslaunch joy_to_twist joy_to_twist.launch
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
