package usecases

import com.fazecast.jSerialComm.SerialPort
import theme.*
import util.bitStuffSymbol

class TryTransmitDataUseCase {

    operator fun invoke(string: String, sourceComName: String, com: SerialPort?): Pair<Boolean, String> {
        if (isDataMatchesToRequirements(string)) {
            val preparedDataPackage = prepareDataPackage(string, sourceComName)
            transmitData(preparedDataPackage, com)
            return true to preparedDataPackage
        }
        return false to ""
    }

    private fun isDataMatchesToRequirements(string: String): Boolean {
        return string.length % N == 0
    }

    private fun prepareDataPackage(string: String, sourceComName: String): String {
        val bitStuffedString = applyBitStuffingIfValid(string.takeLast(N))
        val dataPackage = strWithAddressesAndFlags(bitStuffedString, sourceComName)
        return dataPackage
    }

    private fun strWithAddressesAndFlags(data: String, sourceComName: String) : String {
        val comNum = sourceComName.filter { it.isDigit() }.toInt()
        val binaryComNum = comNum.toString(2).padStart(4, '0')
        return "$BINARY_FLAG$DESTINATION_ADDRESS$binaryComNum$data$FCS"
    }

    private fun applyBitStuffingIfValid(string: String): String {
        val flagLastSymbol = FLAG_FOR_BITSTUFF.last()
        return string.replace(FLAG_FOR_BITSTUFF.toRegex()) { matchResult ->
            matchResult.value.replace(
                "${flagLastSymbol}$".toRegex(),
                "${flagLastSymbol}${bitStuffSymbol()}"
            )
        }
    }

    private fun transmitData(dataPackage: String, com: SerialPort?) {
        if (com != null && com.isOpen) {
            val bytesToSend = dataPackage.toByteArray()
            com.writeBytes(bytesToSend, bytesToSend.size.toLong())
        }
    }
}