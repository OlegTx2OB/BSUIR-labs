package com.example.innowisepexelstestapp.di

import android.content.Context
import androidx.lifecycle.ViewModelProvider
import com.example.innowisepexelstestapp.di.module.AppCiceroneModule
import com.example.innowisepexelstestapp.di.module.AppModule
import com.example.innowisepexelstestapp.di.module.AppViewModelModule
import com.example.innowisepexelstestapp.di.module.DataRoomModule
import com.example.innowisepexelstestapp.di.module.DataNetworkModule
import com.example.innowisepexelstestapp.di.module.DomainRepositoryModule
import com.example.innowisepexelstestapp.di.module.DomainUseCaseModule
import com.example.innowisepexelstestapp.presentation.rv.RvCategoryAdapter
import com.example.innowisepexelstestapp.presentation.view.MainActivity
import dagger.BindsInstance
import dagger.Component
import javax.inject.Singleton

@Singleton
@Component(modules =
   [AppCiceroneModule::class,
    AppViewModelModule::class,
    AppModule::class,
    DomainUseCaseModule::class,
    DomainRepositoryModule::class,
    DataNetworkModule::class,
    DataRoomModule::class]
)
interface AppComponent {

    @Component.Builder
    interface Builder {

        @BindsInstance
        fun applicationContext(context: Context): Builder
        fun build(): AppComponent
    }

    fun provideFactory(): ViewModelProvider.Factory

    fun inject(mainActivity: MainActivity)

    fun inject(categoryHolder: RvCategoryAdapter.CategoryHolder)

}