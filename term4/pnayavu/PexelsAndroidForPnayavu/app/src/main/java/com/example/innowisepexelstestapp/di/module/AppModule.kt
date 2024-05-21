package com.example.innowisepexelstestapp.di.module

import android.content.Context
import com.example.innowisepexelstestapp.util.ResourceProvider
import dagger.Module
import dagger.Provides
import javax.inject.Singleton

@Module
class AppModule {

    @Singleton
    @Provides
    fun provideResourceProvider(mAppContext: Context): ResourceProvider {
        return ResourceProvider(mAppContext)
    }
}