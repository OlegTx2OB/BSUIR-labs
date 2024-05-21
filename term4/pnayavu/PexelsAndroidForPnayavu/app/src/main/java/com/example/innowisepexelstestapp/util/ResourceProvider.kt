package com.example.innowisepexelstestapp.util

import android.content.Context
import android.content.res.ColorStateList
import android.graphics.Typeface
import android.util.TypedValue
import android.view.animation.Animation
import android.view.animation.AnimationUtils
import androidx.annotation.AttrRes
import androidx.core.content.res.ResourcesCompat

class ResourceProvider(private val mAppContext: Context) {

    fun getStringRes(id: Int): String {
        return mAppContext.getString(id)
    }

    fun getAnim(id: Int): Animation {
        return AnimationUtils.loadAnimation(mAppContext, id)
    }

    fun getColor(id: Int): Int {
        return mAppContext.getColor(id)
    }

    fun getFont(id: Int): Typeface {
        return ResourcesCompat.getFont(mAppContext, id)!!
    }

    fun getAttrColor(@AttrRes attributeId: Int, context: Context) : ColorStateList {
        //i know that passing context as a parameter is bad practice, but with mAppContext it doesn't work
        val typedValue = TypedValue()
        context.theme.resolveAttribute(attributeId, typedValue, true)
        return ColorStateList.valueOf(typedValue.data)
    }
}