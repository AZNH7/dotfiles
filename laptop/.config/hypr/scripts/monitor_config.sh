#!/bin/bash

# Define monitor names
eDP1_NAME="eDP-1"  
DP2_NAME="DP-2"    
DP1_NAME="DP-1"

# Define resolutions
eDP1_RESOLUTION="1600x1000"
DP2_RESOLUTION="2560x1440"
DP1_RESOLUTION="2560x1440"

# Function to check if monitor is connected
is_monitor_connected() {
  local monitor_name="$1"
  xrandr | grep -E "$monitor_name connected" >/dev/null 2>&1
  return $?
}

# Check if DP-2 is connected
if is_monitor_connected "$DP2_NAME" ; then
  # Set DP-2 resolution
  xrandr --output "$DP2_NAME" --mode "$DP2_RESOLUTION" --primary
  echo "DP-2 resolution set to $DP2_RESOLUTION"
  xrandr --output "$eDP1_NAME" --off
  echo "eDP-1 turned off"
fi

# Check if eDP-1 is also connected
if is_monitor_connected "$DP1_NAME" ; then
  # Set eDP-1 resolution
  xrandr --output "$eDP1_NAME" --mode "$eDP1_RESOLUTION" --primary --below "$DP2_NAME"
  echo "eDP-1 resolution set to $eDP1_RESOLUTION"
  xrandr --output "$DP1_NAME" --mode "$DP1_RESOLUTION" 
  echo "DP-1 resolution set to $DP1_RESOLUTION"
fi
# else
#   # If DP-2 is not connected, check if eDP-1 is connected
#   if is_monitor_connected "$eDP1_NAME"; then
#     # Set eDP-1 resolution
#     xrandr --output "$eDP1_NAME" --mode "$eDP1_RESOLUTION" --primary
#     echo "eDP-1 resolution set to $eDP1_RESOLUTION"
#   else
#     echo "Neither DP-2 nor eDP-1 are connected"
#   fi
# fi