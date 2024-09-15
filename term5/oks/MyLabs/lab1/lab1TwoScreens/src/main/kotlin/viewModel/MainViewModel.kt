package viewModel

import androidx.compose.runtime.*
import androidx.lifecycle.ViewModel
import com.fazecast.jSerialComm.SerialPort
import theme.strFailed
import theme.strSuccessful

const val SENDER_NAME = "COM1"
const val RECEIVER_NAME = "COM2"
const val BAUD_RATE = 9600

class MainViewModel : ViewModel() {

    private val _sOutputText = mutableStateOf("")
    private val _sSenderText = mutableStateOf("")
    private val _sReceiverText = mutableStateOf("")
    private val _sBaudRate = mutableStateOf(BAUD_RATE)
    private val _sSymbolsCount = mutableStateOf(0)
    private val _selectedReceiverCom = mutableStateOf(RECEIVER_NAME)
    private val _selectedSenderCom = mutableStateOf(SENDER_NAME)

    val sOutputText: State<String> = _sOutputText
    val sSenderText: State<String> = _sSenderText
    val sReceiverText: State<String> = _sReceiverText
    val sBaudRate: State<Int> = _sBaudRate
    val sSymbolsCount: State<Int> = _sSymbolsCount
    val selectedReceiverCom: State<String> = _selectedReceiverCom
    val selectedSenderCom: State<String> = _selectedSenderCom

    private var comSender = createComPort(SENDER_NAME)
    private var comReceiver = createComPort(RECEIVER_NAME)

    init {
        setTextIsSenderComOpened()
        setTextIsReceiverComOpened()
    }

    fun onTextFieldTextChanged(oldText: String, newText: String) {
        if (newText.length > oldText.length) {
            comSender.outputStream.write(newText.last().code)
            _sOutputText.value += comReceiver.inputStream.read().toChar()
            _sSymbolsCount.value++
        }
    }

    fun setSelectedReceiverCom(name: String) {
        _selectedReceiverCom.value = name
        comReceiver.closePort()
        comReceiver = createComPort(name)
        setTextIsReceiverComOpened()
    }

    fun setSelectedSenderCom(name: String) {
        _selectedSenderCom.value = name
        comSender.closePort()
        comSender = createComPort(name)
        setTextIsSenderComOpened()
    }

    private fun createComPort(name: String): SerialPort {
        val newCom = SerialPort.getCommPort(name)
        newCom.baudRate = BAUD_RATE
        return newCom
    }

    private fun setTextIsSenderComOpened() {
        _sSenderText.value = if (comSender.openPort()) {
            strSuccessful
        } else {
            strFailed
        }
    }

    private fun setTextIsReceiverComOpened() {
        _sReceiverText.value = if (comReceiver.openPort()) {
            strSuccessful
        } else {
            strFailed
        }
    }
}
