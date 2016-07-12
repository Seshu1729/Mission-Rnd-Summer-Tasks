from django.conf.urls import url
from . import views

urlpatterns = [
    url(r'^index/$', views.login_page,name="login_page"),
    url(r'^home_page/$', views.home_page,name="home_page"),
    url(r'^index/registration_successfull/$', views.registration_session,name="registration_successfull")
]
