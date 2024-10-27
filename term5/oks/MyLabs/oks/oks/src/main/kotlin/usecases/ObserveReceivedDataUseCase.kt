package usecases

import com.fazecast.jSerialComm.SerialPort
import com.fazecast.jSerialComm.SerialPortDataListener
import com.fazecast.jSerialComm.SerialPortEvent
import theme.FLAG_FOR_BITSTUFF
import theme.HAMMING_BITS_COUNT
import theme.START_FLAGS_ADDRESSES_COUNT
import util.bitStuffSymbol
import kotlin.random.Random

class ObserveReceivedDataUseCase(
    private val getHammingFcsStringUseCase: GetHammingFcsStringUseCase = GetHammingFcsStringUseCase()
) {

    private var string = ""

    operator fun invoke(comReceiver: SerialPort, callback: (String) -> Unit) {
        comReceiver.addDataListener(object : SerialPortDataListener {
            override fun getListeningEvents(): Int {
                return SerialPort.LISTENING_EVENT_DATA_AVAILABLE
            }

            override fun serialEvent(event: SerialPortEvent) {
                if (event.eventType == SerialPort.LISTENING_EVENT_DATA_AVAILABLE) {
                    while (comReceiver.bytesAvailable() > 0) {
                        val receivedByte = comReceiver.inputStream.read()
                        if (receivedByte != -1) {
                            string += receivedByte.toChar()
                        }
                    }
                    if (string != "") {
                        callback(extractDataPackage(string))
                        string = ""
                    }
                }
            }
        })
    }

    private fun extractDataPackage(dataPackage: String): String {
        val strWithoutBitStuffing = strWithoutBitStuffing(dataPackage)
        val strWithFlippedBit = applyFlipBitForErrorSimulation(strWithoutBitStuffing)
        val strWithoutAddressesAndStartFlag = strWithoutAddressesAndStartFlag(strWithFlippedBit)
        val strWithCorrectedFlippedBit = verifyHammingCodeWithCorrection(strWithoutAddressesAndStartFlag)
        val strWithoutFcs = strWithoutFcs(strWithCorrectedFlippedBit)
        return strWithoutFcs
    }

    private fun strWithoutFcs(string: String): String = string.substring(0, string.length - HAMMING_BITS_COUNT)

    private fun strWithoutAddressesAndStartFlag(string: String): String = string.substring(START_FLAGS_ADDRESSES_COUNT)

    private fun strWithoutBitStuffing(string: String): String {
        var matchCount = 0
        return string.replace("${FLAG_FOR_BITSTUFF}${bitStuffSymbol()}".toRegex()) { matchResult ->
            matchCount++
            if (matchCount > 1) {
                matchResult.value.replace(
                    "${bitStuffSymbol()}$".toRegex(), ""
                )
            } else {
                matchResult.value
            }
        }
    }

    private fun applyFlipBitForErrorSimulation(string: String): String {
        if (Random.nextDouble() <= 0.3) {
            val dataStartIndex = START_FLAGS_ADDRESSES_COUNT
            val dataEndIndex = string.length - HAMMING_BITS_COUNT

            val strStartFlags = string.take(dataStartIndex)
            var strData = string.substring(dataStartIndex, dataEndIndex)
            val strFcs = string.takeLast(HAMMING_BITS_COUNT)

            var isBitFlipped = false

            while (!isBitFlipped) {
                val bitToFlipPosition = Random.nextInt(0, strData.length - 1)
                val bitToFlip = strData[bitToFlipPosition]

                if (bitToFlip == '0') {
                    strData = StringBuilder(strData).apply {
                        this[bitToFlipPosition] = '1'
                    }.toString()
                    isBitFlipped = true
                } else if (bitToFlip == '1') {
                    strData = StringBuilder(strData).apply {
                        this[bitToFlipPosition] = '0'
                    }.toString()
                    isBitFlipped = true
                }
            }

            return "$strStartFlags$strData$strFcs"
        } else {
            return string
        }
    }

    private fun verifyHammingCodeWithCorrection(string: String): String {
        val receivedFcs = string.takeLast(HAMMING_BITS_COUNT)
        val calculatedFcs = getHammingFcsStringUseCase(string.take(string.length - HAMMING_BITS_COUNT))

        if(receivedFcs == calculatedFcs) {
            return string
        } else {
            var incorrectBitPosition = 0
            for (i in receivedFcs.indices) {
                if (receivedFcs[i] != calculatedFcs[i]) {
                    incorrectBitPosition += 1 shl i
                }
            }
            val bitToFlip = string[incorrectBitPosition - 1]
            return StringBuilder(string).apply {
                if (bitToFlip == '0') {
                    this[incorrectBitPosition - 1] = '1'
                } else {
                    this[incorrectBitPosition - 1] = '0'
                }
            }.toString()
        }
    }
}