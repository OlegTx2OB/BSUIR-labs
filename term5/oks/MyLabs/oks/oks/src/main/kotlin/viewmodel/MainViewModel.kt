package viewmodel

import androidx.compose.runtime.State
import androidx.compose.runtime.mutableStateOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.fazecast.jSerialComm.SerialPort
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import theme.*
import usecases.ObserveReceivedDataUseCase
import usecases.TryTransmitDataUseCase
import util.bitStuffSymbol

class MainViewModel(
    private val tryTransmitDataUseCase: TryTransmitDataUseCase = TryTransmitDataUseCase(),
    private val observeReceivedDataUseCase: ObserveReceivedDataUseCase = ObserveReceivedDataUseCase(),
) : ViewModel() {

    private val _sIsInputTextFieldVisible = mutableStateOf(false)
    private val _sIsOutputTextFieldVisible = mutableStateOf(false)
    private val _sOutputText = mutableStateOf("")
    private val _sSelectedSenderComName = mutableStateOf(strNotSelected)
    private val _sSelectedReceiverComName = mutableStateOf(strNotSelected)
    private val _sSenderComStateText = mutableStateOf(strClear)
    private val _sReceiverComStateText = mutableStateOf(strClear)
    private val _sBaudRate = mutableStateOf(BAUD_RATE)
    private val _sStopBits = mutableStateOf(STOP_BITS)
    private val _sDataBits = mutableStateOf(DATA_BITS)
    private val _sParity = mutableStateOf(PARITY)
    private val _sTimeoutMode = mutableStateOf(TIMEOUT_MODE)
    private val _sReadTimeout = mutableStateOf(READ_TIMEOUT)
    private val _sWriteTimeout = mutableStateOf(WRITE_TIMEOUT)
    private val _sTransferredSymbolsCount = mutableStateOf(0)
    private val _sCurrentPackageString = mutableStateOf(strNa)
    private val _sComList = mutableStateOf(returnNewComList())

    private var comSender: SerialPort? = null
    private var comReceiver: SerialPort? = null

    sealed interface MainState {
        sealed interface Input {
            val sIsInputTextFieldVisible: State<Boolean>

            fun onTextFieldValueChange(oldText: String, newText: String): String
        }
        sealed interface Output {
            val sIsOutputTextFieldVisible: State<Boolean>
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
            val sDataBits: State<Int>
            val sStopBits: State<Int>
            val sParity: State<Int>
            val sTimeoutMode: State<Int>
            val sReadTimeout: State<Int>
            val sWriteTimeout: State<Int>
            val sTransferredSymbolsCount: State<Int>
            val sCurrentPackageString: State<String>
        }
    }

    inner class MainStateImpl {
        inner class InputImpl : MainState.Input {
            override val sIsInputTextFieldVisible: State<Boolean> = _sIsInputTextFieldVisible

            override fun onTextFieldValueChange(oldText: String, newText: String): String {
                val regex = Regex("^[01\\n]*$")
                return if (
                    (oldText.isEmpty()
                    || oldText == newText.dropLast(1))
                    && regex.matches(newText)
                ) {
                    viewModelScope.launch(Dispatchers.IO) {
                        val result = tryTransmitDataUseCase(newText, _sSelectedSenderComName.value, comSender)
                        if (result.first) {
                            _sTransferredSymbolsCount.value += result.second.length
                            _sCurrentPackageString.value = transformStringWithFlagsAndNewLines(result.second)
                        }
                    }
                    newText
                } else {
                    oldText
                }
            }
        }

        inner class OutputImpl : MainState.Output {
            override val sIsOutputTextFieldVisible: State<Boolean> = _sIsOutputTextFieldVisible
            override val sOutputText: State<String> = _sOutputText
        }

        inner class ControlImpl : MainState.Control {
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
                    _sComList.value = returnNewComListWithoutComPairs()
                }
            }

            override fun setSelectedReceiverCom(name: String) {
                _sReceiverComStateText.value = strLoading
                _sSelectedReceiverComName.value = name
                viewModelScope.launch(Dispatchers.IO) {
                    comReceiver = resetCom(comReceiver, name)
                    observeReceivedDataUseCase(comReceiver!!) { newString ->
                        _sOutputText.value += newString
                    }
                    updateUiOnReceiverComOpening()
                    _sComList.value = returnNewComListWithoutComPairs()
                }
            }
        }

        inner class StateImpl : MainState.Status {
            override val sStopBits: State<Int> = _sStopBits
            override val sDataBits: State<Int> = _sDataBits
            override val sParity: State<Int> = _sParity
            override val sBaudRate: State<Int> = _sBaudRate
            override val sTimeoutMode: State<Int> = _sTimeoutMode
            override val sReadTimeout: State<Int> = _sReadTimeout
            override val sWriteTimeout: State<Int> = _sWriteTimeout
            override val sTransferredSymbolsCount: State<Int> = _sTransferredSymbolsCount
            override val sCurrentPackageString: State<String> = _sCurrentPackageString
        }
    }

    private fun transformStringWithFlagsAndNewLines(string: String): String {
        val newLinesReplacedString = string.replace("\n", "\\n")
        var matchCount = 0

        val stringWithHighlightedBitstuff = newLinesReplacedString.replace(
            "$FLAG_FOR_BITSTUFF${bitStuffSymbol()}".toRegex()
        ) { matchResult ->
            matchCount++
            if (matchCount > 1) {
                matchResult.value.replace(
                    "${bitStuffSymbol()}$".toRegex(),
                    "$BITSTUFF_SEPARATOR${bitStuffSymbol()}$BITSTUFF_SEPARATOR"
                )
            } else {
                matchResult.value
            }
        }

        val stringWithSeparationBeforeHamming = stringWithHighlightedBitstuff.run {
            var symbolsCountBeforeSeparation = HAMMING_BITS_COUNT
            if (stringWithHighlightedBitstuff.takeLast(HAMMING_BITS_COUNT).contains(BITSTUFF_SEPARATOR)) {
                symbolsCountBeforeSeparation += 2
            }
            this.take(this.length - symbolsCountBeforeSeparation) +
                    HAMMING_SEPARATOR +
                    this.drop(this.length - symbolsCountBeforeSeparation)
        }

        return stringWithSeparationBeforeHamming
    }

    private fun returnNewComList(): MutableList<String> {
        val comList = mutableListOf<String>()
        for (i in 1..15) {
            comList.add("$stcCom$i")
        }
        return comList
    }

    private fun returnNewComListWithoutComPairs(): MutableList<String> {
        val newList = returnNewComList()

        val senderComName = _sSelectedSenderComName.value
        val receiverComName = _sSelectedReceiverComName.value

        if (senderComName != strNotSelected) {
            val senderPlusOneComName = "$stcCom${senderComName.filter { it.isDigit() }.toInt() + 1}"
            newList.remove(senderComName)
            newList.remove(senderPlusOneComName)
        }

        if (receiverComName != strNotSelected) {
            val receiverMinusOneComName = "$stcCom${receiverComName.filter { it.isDigit() }.toInt() - 1}"
            newList.remove(receiverComName)
            newList.remove(receiverMinusOneComName)
        }

        return newList
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
            _sIsOutputTextFieldVisible.value = true
            _sReceiverComStateText.value = strSuccessful
        } else {
            _sIsOutputTextFieldVisible.value = false
            _sReceiverComStateText.value = strFailed
        }
    }

    private fun resetCom(com: SerialPort?, newName: String): SerialPort {
        com?.closePort()
        val newCom = SerialPort.getCommPort(newName)
        newCom.baudRate = _sBaudRate.value
        newCom.parity = _sParity.value
        newCom.numDataBits = _sDataBits.value
        newCom.numStopBits = _sStopBits.value
        newCom.setComPortTimeouts(
            _sTimeoutMode.value,
            _sReadTimeout.value,
            _sWriteTimeout.value
        )
        newCom.openPort()

        return newCom
    }

}
