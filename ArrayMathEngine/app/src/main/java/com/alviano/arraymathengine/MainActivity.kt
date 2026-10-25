package com.alviano.arraymathengine

import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity

class MainActivity : ComponentActivity() {
    init {
        System.loadLibrary("native-lib")
    }

    private external fun calculateAverage(numbers: IntArray): Float
    private external fun reverseAndUppercaseString(input: String): String
    private external fun xorEncryptDecrypt(data: ByteArray, key: Byte): ByteArray
    private external fun processUser(user: User): UserStats

    private fun res1() {
        val sampleDate = intArrayOf(10, 20, 30, 40, 50)
        val result = calculateAverage(sampleDate)

        Log.d("JNI_TEST", "Hasil rata-rata dari cpp: $result")
    }

    private fun res2() {
        val originalText = "hello android native"
        val transformedText = reverseAndUppercaseString(originalText)
        Log.d("JNI_TEST", "Original : $originalText")
        Log.d("JNI_TEST", "Transform: $transformedText")
    }

    private fun res3() {
        val secretMessage = "Data Rahasia NDK"
        val rawBytes = secretMessage.toByteArray(Charsets.UTF_8)
        val secretKey: Byte = 0x5A

        val encryptedBytes = xorEncryptDecrypt(rawBytes, secretKey)
        val encryptedString = String(encryptedBytes, Charsets.UTF_8)

        val decryptedBytes = xorEncryptDecrypt(encryptedBytes, secretKey)
        val decryptedString = String(decryptedBytes, Charsets.UTF_8)

        Log.d("JNI_TEST", "Original Text : $secretMessage")
        Log.d("JNI_TEST", "Encrypted Text: $encryptedString")
        Log.d("JNI_TEST", "Decrypted Text: $decryptedString")
    }

    private fun res4() {
        val inputUser = User(name = "Alvin", age = 18)
        val resultStats = processUser(inputUser)

        Log.d("JNI_TEST", "Input User  : $inputUser")
        Log.d("JNI_TEST", "Greeting    : ${resultStats.greeting}")
        Log.d("JNI_TEST", "Is Adult?   : ${resultStats.isAdult}")
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        res1()
        res2()
        res3()
    }
}
