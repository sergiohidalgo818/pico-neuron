#!/usr/bin/env python
import serial
import getpass
import grp
import os
import logging
import signal
import sys
import argparse
import time
import pandas as pd


class DataWriter:
    directory: str
    filename: str
    separator: str

    def __init__(
        self,
        directory: str,
        filename: str,
        separator: str,
    ):
        self.directory = directory
        self.filename = filename
        self.separator = separator

    def write(self, x: list[float], t: list[float]):
        dataframe: pd.DataFrame = pd.DataFrame({"x": x, "time": t})
        dataframe.to_csv(
            self.directory + self.filename, sep=self.separator, index=False
        )


data_writer: DataWriter

x: list[float] = []
t: list[float] = []

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger("python_reciver")


def signal_handler(sig, frame) -> None:
    logger.info("Saving data on " + data_writer.directory + data_writer.filename)
    data_writer.write(x, t)
    sys.exit(0)


def check_permissions():
    user = getpass.getuser()

    # Check if running as root
    if os.geteuid() == 0:
        logger.error("Do not run this script as root. Please run it as a normal user.")
        sys.exit(1)

    # Check if user is in 'dialout' group
    try:
        groups = [g.gr_name for g in grp.getgrall() if user in g.gr_mem]
        gid_groups = [grp.getgrgid(g).gr_name for g in os.getgroups()]
        all_groups = set(groups + gid_groups)

        if "dialout" not in all_groups:
            logger.error(f"User '{user}' is not in the 'dialout' group.")
            logger.info("To fix this, run: sudo usermod -aG dialout $USER")
            logger.info("Then log out and log back in.")
            sys.exit(1)
    except Exception:
        logger.exception("Error while checking user permissions.")
        sys.exit(1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        "Script to capture and write the signals from the raspberry, for debugging purposes"
    )
    parser.add_argument(
        "-d",
        "--directory",
        help="Directory to save the data",
        type=str,
        default="data/",
    )
    parser.add_argument(
        "-f",
        "--filename",
        help="Filename for the data",
        type=str,
        default="hindmarsh-rose.csv",
    )
    parser.add_argument(
        "-s", "--separator", help="Separator for the data csv", type=str, default=" "
    )
    parser.add_argument(
        "-sn",
        "--serial-name",
        help="Serial name for the raspberry pi",
        type=str,
        default="/dev/ttyUSB0",
    )
    parser.add_argument(
        "-si",
        "--serial-id",
        help="Serial id for the raspberry pi",
        type=int,
        default=9600,
    )
    parser.add_argument(
        "-ut",
        "--use-timer",
        help="NOT RECOMENDED. Use python timer to set the data time",
        action="store_true",
        default=False,
    )
    parser.add_argument(
        "-ti",
        "--time-incremet",
        help="Only works when --use-timer is not set, the time increment for the data",
        type=float,
        default=0.001,
    )

    args = parser.parse_args()

    check_permissions()

    data_writer = DataWriter(args.directory, args.filename, args.separator)

    signal.signal(signal.SIGINT, signal_handler)
    logger.info("Press Ctrl+C to save the file with the data")

    ser = serial.Serial(args.serial_name, args.serial_id, timeout=1)

    to_secs: int = 1000000000
    initial_time: float

    if args.use_timer:
        initial_time = time.perf_counter_ns() / to_secs
    else:
        initial_time = 0

    while True:
        raw: bytes = ser.readline()

        try:
            line: str = raw.decode("utf-8").strip()
            try:
                value: float = float(line)
                x.append(value)
                if args.use_timer:
                    t.append(float((time.perf_counter_ns() - initial_time) / to_secs))
                else:
                    t.append(initial_time)
                    initial_time += args.time_incremet

            except ValueError as e:
                logger.error(e)
        except UnicodeDecodeError as e:
            logger.error(e)
