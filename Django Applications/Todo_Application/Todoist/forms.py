from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.models import User
from django import forms

class register_users(UserCreationForm):
    username = forms.CharField(max_length=256)
    password = forms.CharField(max_length=256)