package viewmodel

import androidx.compose.runtime.State
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.fazecast.jSerialComm.SerialPort
import com.fazecast.jSerialComm.SerialPortDataListener
import com.fazecast.jSerialComm.SerialPortEvent
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import theme.*

const val BAUD_RATE = 9600

class MainViewModel : ViewModel() {

    private val _sIsInputTextFieldVisible = mutableStateOf(false)
    private val _sIsOutputTextVisible = mutableStateOf(false)
    private val _sOutputText = mutableStateOf("")
    private val _sSelectedSenderComName = mutableStateOf(strNotSelected)
    private val _sSelectedReceiverComName = mutableStateOf(strNotSelected)
    private val _sSenderComStateText = mutableStateOf(strClear)
    private val _sReceiverComStateText = mutableStateOf(strClear)
    private val _sBaudRate = mutableStateOf(BAUD_RATE)
    private val _sTransferredSymbolsCount = mutableStateOf(0)
    private val _sComList = mutableStateOf(returnNewComList())

    private var comSender: SerialPort? = null
    private var comReceiver: SerialPort? = null


    sealed interface MainState {
        sealed interface Input {
            val sIsInputTextFieldVisible: State<Boolean>

            fun onTextFieldValueChange(oldText: String, newText: String): String
        }
        sealed interface Output {
            val sIsOutputTextVisible: State<Boolean>
            val sOutputText: State<String>
        }
        sealed interface Control {
            val sSelectedSenderComName: State<String>
            val sSelectedReceiverComName: State<String>
            val sSenderComStateText: State<String>
            val sReceiverComStateText: State<String>
            val sComList: State<List<String>>

            fun setSelectedSenderCom(name: String)
            fun setSelectedReceiverCom(name: String)
        }
        sealed interface Status {
            val sBaudRate: State<Int>
            val sTransferredSymbolsCount: State<Int>
        }
    }


    private fun returnNewComList(): MutableList<String> {
        val comList = mutableListOf<String>()
        for (i in 1..255) {
            comList.add("COM$i")
        }
        return comList
    }

    private fun returnNewComListWithoutPairOf(comName: String, isItSenderCom: Boolean): MutableList<String> {
        val secondComName = if (isItSenderCom) {
            "COM${comName.filter { it.isDigit() }.toInt() + 1}"
        } else {
            "COM${comName.filter { it.isDigit() }.toInt() - 1}"
        }
        val newList = returnNewComList()
        newList.remove(comName)
        newList.remove(secondComName)
        return newList
    }

    private fun sendCharIntoCom(char: Char) {
        comSender!!.outputStream.write(char.code)
    }

    private fun updateUiOnSenderComOpening() {
        if (comSender!!.isOpen) {
            _sIsInputTextFieldVisible.value = true
            _sSenderComStateText.value = strSuccessful
        } else {
            _sIsInputTextFieldVisible.value = false
            _sSenderComStateText.value = strFailed
        }
    }

    private fun updateUiOnReceiverComOpening() {
        if (comReceiver!!.isOpen) {
            _sIsOutputTextVisible.value = true
            _sReceiverComStateText.value = strSuccessful
        } else {
            _sIsOutputTextVisible.value = false
            _sReceiverComStateText.value = strFailed
        }
    }

    private fun resetCom(com: SerialPort?, newName: String): SerialPort {
        com?.closePort()
        val newCom = SerialPort.getCommPort(newName)
        newCom.baudRate = _sBaudRate.value
        newCom.openPort()
        return newCom
    }

    inner class InputStateImpl : MainState.Input {
        override val sIsInputTextFieldVisible: State<Boolean> = _sIsInputTextFieldVisible
        
        override fun onTextFieldValueChange(oldText: String, newText: String): String {
            return if (
                oldText.isEmpty()
                || oldText == newText.dropLast(1)
                ) {
                viewModelScope.launch(Dispatchers.IO) {
                    sendCharIntoCom(newText.last())
                }
                newText
            } else {
                oldText
            }
        }
    }

    inner class OutputStateImpl : MainState.Output {
        override val sIsOutputTextVisible: State<Boolean> = _sIsOutputTextVisible
        override val sOutputText: State<String> = _sOutputText
    }

    inner class ControlStateImpl : MainState.Control {
        override val sSelectedSenderComName: State<String> = _sSelectedSenderComName
        override val sSelectedReceiverComName: State<String> = _sSelectedReceiverComName
        override val sSenderComStateText: State<String> = _sSenderComStateText
        override val sReceiverComStateText: State<String> = _sReceiverComStateText
        override val sComList: State<List<String>> = _sComList

        override fun setSelectedSenderCom(name: String) {
            _sSenderComStateText.value = strLoading
            _sSelectedSenderComName.value = name
            viewModelScope.launch(Dispatchers.IO) {
                comSender = resetCom(comSender, name)
                updateUiOnSenderComOpening()
                _sComList.value = returnNewComList()//returnNewComListWithoutPairOf(name, true)
            }
        }

        override fun setSelectedReceiverCom(name: String) {
            _sReceiverComStateText.value = strLoading
            _sSelectedReceiverComName.value = name
            viewModelScope.launch(Dispatchers.IO) {
                comReceiver = resetCom(comReceiver, name)
                comReceiver!!.addDataListener(object : SerialPortDataListener {
                    override fun getListeningEvents(): Int {
                        return SerialPort.LISTENING_EVENT_DATA_AVAILABLE
                    }

                    override fun serialEvent(event: SerialPortEvent) {
                        if (event.eventType == SerialPort.LISTENING_EVENT_DATA_AVAILABLE) {
                            while (comReceiver!!.bytesAvailable() > 0) {
                                val receivedByte = comReceiver!!.inputStream.read()
                                if (receivedByte != -1) { // Проверяем, что чтение прошло успешно
                                    _sOutputText.value += receivedByte.toChar() // Добавляем полученный символ в строку
                                    _sTransferredSymbolsCount.value++
                                }
                            }
                        }
                    }
                })
                updateUiOnReceiverComOpening()
                _sComList.value = returnNewComList()//returnNewComListWithoutPairOf(name, false)
            }
        }
    }

    inner class StateStateImpl : MainState.Status {
        override val sBaudRate: State<Int> = _sBaudRate
        override val sTransferredSymbolsCount: State<Int> = _sTransferredSymbolsCount
    }

}

