package usecases

import theme.HAMMING_BITS_COUNT

class GetHammingFcsStringUseCase {

    operator fun invoke(string: String): String {
        var hammingCodeString = ""
        for (flagNumber in 0 until HAMMING_BITS_COUNT) {
            val powerOfTwo = 1 shl flagNumber
            var hammingFlagSymbol = 0
            for (startPosition in powerOfTwo - 1 until string.length step powerOfTwo * 2) {
                for (i in 0 until powerOfTwo) {
                    if (startPosition + i >= string.length) {
                        break
                    }
                    if (string[startPosition + i] == '1') {
                        hammingFlagSymbol = if (hammingFlagSymbol == 0) {
                            1
                        } else {
                            0
                        }
                    }
                }

            }
            hammingCodeString = "$hammingCodeString$hammingFlagSymbol"
        }
        return hammingCodeString
    }
}