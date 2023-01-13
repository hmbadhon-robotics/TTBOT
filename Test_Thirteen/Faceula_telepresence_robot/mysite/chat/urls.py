from django.urls import path
from .views import *
urlpatterns = [
    path('', peer, name='peer'),
    path('peer1/', peer1, name='peer1'),
    path('peer2/', peer2, name='peer2'),
]