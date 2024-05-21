package com.example.innowisepexelstestapp

import android.app.Application
import com.example.innowisepexelstestapp.di.AppComponent
import com.example.innowisepexelstestapp.di.DaggerAppComponent

//FOR PNAYAVU
class App : Application() {

    val appComponent: AppComponent by lazy(
        DaggerAppComponent
            .builder()
            .applicationContext(this)::build
    )

    override fun onCreate() {
        super.onCreate()
        instance = this
    }

    companion object {
        internal lateinit var instance: App
            private set
    }

}