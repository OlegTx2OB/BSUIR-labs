package viewmodel

import androidx.compose.runtime.State
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.fazecast.jSerialComm.SerialPort
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import theme.*

const val BAUD_RATE = 9600

class MainViewModel : ViewModel() {

    private val _sOutputText = mutableStateOf("")
    private val _sSelectedSenderComName = mutableStateOf(strNotSelected)
    private val _sSelectedReceiverComName = mutableStateOf(strNotSelected)
    private val _sSenderComStateText = mutableStateOf(strClear)
    private val _sReceiverComStateText = mutableStateOf(strClear)
    private val _sBaudRate = mutableStateOf(BAUD_RATE)
    private val _sSymbolsCount = mutableStateOf(0)
    private val _sComList = mutableStateOf(returnNewComList())

    private var comSender: SerialPort? = null
    private var comReceiver: SerialPort? = null


    sealed interface InputState {
        fun onTextFieldValueChange(oldText: String, newText: String): String
    }
    sealed interface OutputState {
        val sOutputText: State<String>
    }
    sealed interface ControlState {
        val sSelectedSenderComName: State<String>
        val sSelectedReceiverComName: State<String>
        val sSenderComStateText: State<String>
        val sReceiverComStateText: State<String>
        val sComList: State<List<String>>

        fun setSelectedSenderCom(name: String)
        fun setSelectedReceiverCom(name: String)
    }
    sealed interface StateState {
        val sBaudRate: State<Int>
        val sSymbolsCount: State<Int>
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
        TODO()
    }

    private fun setTextIsSenderComOpened() {
        _sSenderComStateText.value = strLoading
        _sSenderComStateText.value = if (comSender!!.openPort()) {
            strSuccessful
        } else {
            strFailed
        }
    }

    private fun setTextIsReceiverComOpened() {
        _sReceiverComStateText.value = strLoading
        _sReceiverComStateText.value = if (comReceiver!!.openPort()) {
            strSuccessful
        } else {
            strFailed
        }
    }

    inner class InputStateImpl : InputState {
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

    inner class OutputStateImpl : OutputState {
        override val sOutputText: State<String> = _sOutputText
    }

    inner class ControlStateImpl : ControlState {
        override val sSelectedSenderComName: State<String> = _sSelectedSenderComName
        override val sSelectedReceiverComName: State<String> = _sSelectedReceiverComName
        override val sSenderComStateText: State<String> = _sSenderComStateText
        override val sReceiverComStateText: State<String> = _sReceiverComStateText
        override val sComList: State<List<String>> = _sComList

        override fun setSelectedSenderCom(name: String) {
            _sComList.value = returnNewComListWithoutPairOf(name, true)
            _sSelectedSenderComName.value = name
            comSender = SerialPort.getCommPort(name)
            comSender!!.baudRate = _sBaudRate.value
            viewModelScope.launch(Dispatchers.IO) {
                setTextIsSenderComOpened()
            }
        }

        override fun setSelectedReceiverCom(name: String) {
            _sComList.value = returnNewComListWithoutPairOf(name, false)
            _sSelectedReceiverComName.value = name
            comReceiver = SerialPort.getCommPort(name)
            comReceiver!!.baudRate = _sBaudRate.value
            viewModelScope.launch(Dispatchers.IO) {
                setTextIsReceiverComOpened()
            }
        }
    }

    inner class StateStateImpl : StateState {
        override val sBaudRate: State<Int> = _sBaudRate
        override val sSymbolsCount: State<Int> = _sSymbolsCount
    }

}

