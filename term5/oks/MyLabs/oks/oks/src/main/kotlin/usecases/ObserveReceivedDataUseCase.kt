package usecases

import com.fazecast.jSerialComm.SerialPort
import com.fazecast.jSerialComm.SerialPortDataListener
import com.fazecast.jSerialComm.SerialPortEvent
import theme.FLAG_FOR_BITSTUFF
import util.bitStuffSymbol

class ObserveReceivedDataUseCase {

    private var string = ""

    operator fun invoke(name: String, comReceiver: SerialPort, callback: (String) -> Unit) {
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
        val strWithoutAddressesAndFlags = strWithoutAddressesAndFlags(dataPackage)
        return strWithoutBitStuffing(strWithoutAddressesAndFlags)
    }

    private fun strWithoutAddressesAndFlags(dataPackage: String): String {
        val strWithoutAddresses = dataPackage.substring(16)
        return strWithoutAddresses.substring(0, strWithoutAddresses.length - 1)
    }

    private fun strWithoutBitStuffing(string: String): String {
        return string.replace("${FLAG_FOR_BITSTUFF}${bitStuffSymbol()}".toRegex()) { matchResult ->
            matchResult.value.replace(
                "${bitStuffSymbol()}$".toRegex(), ""
            )
        }
    }
}