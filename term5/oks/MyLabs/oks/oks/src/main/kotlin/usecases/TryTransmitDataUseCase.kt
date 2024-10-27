package usecases

import com.fazecast.jSerialComm.SerialPort
import theme.*
import util.bitStuffSymbol

class TryTransmitDataUseCase(
    private val getHammingFcsStringUseCase: GetHammingFcsStringUseCase = GetHammingFcsStringUseCase()
) {

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
        val strWithHammingCode = applyHammingCode(string.takeLast(N))
        val strWithAddressesAndStartFlag = applyAddressesAndStartFlag(strWithHammingCode, sourceComName)
        val strWithBitStuffing = applyBitStuffingIfValid(strWithAddressesAndStartFlag)
        return strWithBitStuffing
    }

    private fun applyAddressesAndStartFlag(dataWithHamming: String, sourceComName: String) : String {
        val comNum = sourceComName.filter { it.isDigit() }.toInt()
        val binaryComNum = comNum.toString(2).padStart(4, '0')
        return "$BINARY_FLAG$DESTINATION_ADDRESS$binaryComNum$dataWithHamming"
    }

    private fun applyBitStuffingIfValid(string: String): String {
        val flagLastSymbol = FLAG_FOR_BITSTUFF.last()
        var matchCount = 0

        return string.replace(
            FLAG_FOR_BITSTUFF.toRegex()
        ) { matchResult ->
            matchCount++
            if (matchCount > 1) {
                matchResult.value.replace(
                    "${flagLastSymbol}$".toRegex(),
                    "${flagLastSymbol}${bitStuffSymbol()}"
                )
            } else {
                matchResult.value
            }
        }
    }

    private fun transmitData(dataPackage: String, com: SerialPort?) {
        if (com != null && com.isOpen) {
            val bytesToSend = dataPackage.toByteArray()
            com.writeBytes(bytesToSend, bytesToSend.size.toLong())
        }
    }

    private fun applyHammingCode(string: String): String = "$string${getHammingFcsStringUseCase(string)}"

}