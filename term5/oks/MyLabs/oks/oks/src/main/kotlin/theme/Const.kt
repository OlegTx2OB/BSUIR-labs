package theme

import com.fazecast.jSerialComm.SerialPort
import kotlin.math.ceil
import kotlin.math.ln

const val BAUD_RATE = 9600
const val PARITY = SerialPort.NO_PARITY // 0
const val DATA_BITS = 8
const val STOP_BITS = SerialPort.ONE_STOP_BIT // 1
const val TIMEOUT_MODE = SerialPort.TIMEOUT_NONBLOCKING //0
const val READ_TIMEOUT = 0
const val WRITE_TIMEOUT = 0

const val N = 24
const val FLAG_FOR_BITSTUFF = "1001100"
const val BINARY_FLAG = "10011001"
const val DESTINATION_ADDRESS = "0000"
const val BITSTUFF_SEPARATOR = '|'
const val HAMMING_SEPARATOR = ' '
const val START_FLAGS_ADDRESSES_COUNT = 16
val HAMMING_BITS_COUNT = ceil(ln(N.toDouble()) / ln(2.0)).toInt()