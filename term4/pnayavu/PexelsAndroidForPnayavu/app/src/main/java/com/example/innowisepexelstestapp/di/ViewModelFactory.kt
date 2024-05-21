package com.example.innowisepexelstestapp.di

import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment
import androidx.lifecycle.LifecycleOwner
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import com.example.innowisepexelstestapp.App
import javax.inject.Inject
import javax.inject.Provider
import kotlin.reflect.KClass

class ViewModelFactory @Inject constructor(
    private val models: MutableMap<Class<out ViewModel>, Provider<ViewModel>>
) : ViewModelProvider.Factory {
    override fun <T : ViewModel> create(modelClass: Class<T>): T {
        val viewModelProvider = models[modelClass]
            ?: throw IllegalArgumentException("$modelClass not found")

        @Suppress("UNCHECKED_CAST")
        return viewModelProvider.get() as T
    }
}

inline fun <T, reified VM : ViewModel> T.injectViewModel(
    viewModelClass: KClass<VM> = VM::class
) where T : AppCompatActivity, T : LifecycleOwner = lazy(this) {
    ViewModelProvider(
        this,
        (this.application as App).appComponent.provideFactory()
    )[viewModelClass.java]
}

inline fun <T, reified VM : ViewModel> T.injectViewModel(
    viewModelClass: KClass<VM> = VM::class
) where T : Fragment, T : LifecycleOwner = lazy(this) {
    ViewModelProvider(
        this,
        (activity!!.application as App).appComponent.provideFactory()
    )[viewModelClass.java]
}